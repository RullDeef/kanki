#include <algorithm>
#include <fstream>
#include <stdexcept>
#include "tools/logger.hpp"
#include "tools/idgenerator.hpp"
#include "db/model/sessionbuilder.hpp"
#include "db/model/sessionparser.hpp"
#include "db/filereader.hpp"
#include "db/filewriter.hpp"
#include "filesessionrepo.hpp"

FileSessionRepository::FileSessionRepository(std::shared_ptr<IDTOIOFactory> ioFactory)
    : ioFactory(ioFactory)
{
    if (ioFactory)
        load();
}

FileSessionRepository::~FileSessionRepository()
{
    try
    {
        dump();
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD(e.what());
    }
}

void FileSessionRepository::load()
{
    auto reader = ioFactory->createReader();
    load(*reader);
}

void FileSessionRepository::load(IDTOReader &reader)
{
    sessions.clear();

    size_t sessionsCount = reader.readCount();
    for (size_t i = 0; i < sessionsCount; i++)
    {
        auto dbSession = reader.readSessionDTO();
        DBSessionBuilder builder(dbSession);

        size_t snapshotsCount = reader.readCount();
        for (size_t j = 0; j < snapshotsCount; j++)
        {
            auto snapshotDTO = reader.readSnapshotDTO();
            builder.addSnapshotDTO(snapshotDTO);
        }

        sessions.push_back(builder.build());
    }
}

void FileSessionRepository::dump()
{
    auto writer = ioFactory->createWriter();
    dump(*writer);
}

void FileSessionRepository::dump(IDTOWriter &writer)
{
    writer.writeCount(sessions.size());
    for (auto session : sessions)
    {
        DBSessionParser parser(session);
        writer.writeSessionDTO(parser.getSession());

        auto dbSnapshots = parser.getSnapshots();
        writer.writeCount(dbSnapshots.size());

        for (auto snapshotDTO : dbSnapshots)
            writer.writeSnapshotDTO(snapshotDTO);
    }
}

std::list<Session> FileSessionRepository::getSessions()
{
    return sessions;
}

Session FileSessionRepository::getSession(UUID id)
{
    auto iter = std::find_if(sessions.begin(), sessions.end(),
                             [id](const Session &session)
                             { return session.getId() == id; });

    if (iter == sessions.end())
        throw std::runtime_error("invalid id");
    return *iter;
}

void FileSessionRepository::removeSession(UUID id)
{
    sessions.erase(
        std::remove_if(sessions.begin(), sessions.end(),
                       [id](const Session &session)
                       { return session.getId() == id; }),
        sessions.end());
}

void FileSessionRepository::saveSession(const Session &session)
{
    auto id = session.getId();
    auto iter = std::find_if(sessions.begin(), sessions.end(),
                             [id](const Session &session)
                             { return session.getId() == id; });

    if (iter != sessions.end())
        *iter = session;
    else
        sessions.push_back(session);
}
