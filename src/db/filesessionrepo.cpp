#include <algorithm>
#include <fstream>
#include <stdexcept>
#include "tools/logger.hpp"
#include "tools/idgenerator.hpp"
#include "dto/sessionbuilder.hpp"
#include "dto/sessionparser.hpp"
#include "db/filereader.hpp"
#include "db/filewriter.hpp"
#include "filesessionrepo.hpp"

std::list<Session> FileSessionRepository::getSessions()
{
    return sessions;
}

Session FileSessionRepository::getSession(size_t id)
{
    auto iter = std::find_if(sessions.begin(), sessions.end(),
                             [id](const Session &session)
                             { return session.getId() == id; });

    if (iter == sessions.end())
        throw std::runtime_error("invalid id");
    return *iter;
}

void FileSessionRepository::removeSession(size_t id)
{
    sessions.erase(
        std::remove_if(sessions.begin(), sessions.end(),
                       [id](const Session &session)
                       { return session.getId() == id; }),
        sessions.end());
}

void FileSessionRepository::saveSession(const Session &session)
{
    size_t id = session.getId();
    auto iter = std::find_if(sessions.begin(), sessions.end(),
                             [id](const Session &session)
                             { return session.getId() == id; });

    if (iter != sessions.end())
        *iter = session;
    else
        sessions.push_back(session);
}

void FileSessionRepository::load(IDTOReader &reader)
{
    sessions.clear();

    size_t sessionsCount = reader.readCount();
    for (size_t i = 0; i < sessionsCount; i++)
    {
        auto sessionDTO = reader.readSessionDTO();
        DTOSessionBuilder builder(sessionDTO);

        size_t snapshotsCount = reader.readCount();
        for (size_t j = 0; j < snapshotsCount; j++)
        {
            auto snapshotDTO = reader.readSnapshotDTO();
            builder.addSnapshotDTO(snapshotDTO);
        }

        sessions.push_back(builder.build());
    }
}

void FileSessionRepository::dump(IDTOWriter &writer)
{
    writer.writeCount(sessions.size());
    for (auto session : sessions)
    {
        DTOSessionParser parser(session);
        writer.writeSessionDTO(parser.getSessionDTO());

        auto snapshotDTOs = parser.getSnapshotDTOs();
        writer.writeCount(snapshotDTOs.size());

        for (auto snapshotDTO : snapshotDTOs)
            writer.writeSnapshotDTO(snapshotDTO);
    }
}
