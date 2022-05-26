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

FileSessionRepository::FileSessionRepository(ICollectionRepository *collectionRepo, const std::string &filename)
    : filename(filename), collectionRepo(collectionRepo)
{
    try
    {
        load();
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD(e.what());
    }
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

void FileSessionRepository::load()
{
    sessions.clear();

    std::wifstream file(filename);
    FileReader reader(file);

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

        /// KOSTILY: updating snapshot cards with collection repository
        auto session = updateSessionCards(builder.build());
        sessions.push_back(session);
    }
}

void FileSessionRepository::dump()
{
    std::wofstream file(filename);
    FileWriter writer(file);

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

Session FileSessionRepository::updateSessionCards(const Session& session)
{
    Session newSession(session.getId(), session.getStartTime(), session.getEndTime());

    for (auto snapshot : session)
        newSession.addSnapshot(Snapshot(findCardById(snapshot.getCard().getId()),
                                        snapshot.getParamType(),
                                        snapshot.getKnowledgeDegree(),
                                        snapshot.getTimePoint()));

    return std::move(newSession);
}

Card FileSessionRepository::findCardById(size_t cardId)
{
    auto collections = collectionRepo->getCollections();

    for (auto collection : collections)
        for (auto deck : collection)
            for (auto card : deck)
                if (card.getId() == cardId)
                    return card;

    throw std::runtime_error("could not find card with given id");
}
