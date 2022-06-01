#include "tools/logger.hpp"
#include "tools/idgenerator.hpp"
#include "sessionmanager.hpp"

SessionManager::SessionManager(std::shared_ptr<ISessionRepository> sessionRepository)
    : sessionRepository(sessionRepository), activeSession(IdGenerator()())
{
}

SessionManager::~SessionManager()
{
    try
    {
        activeSession.endSession();
        sessionRepository->saveSession(activeSession);
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD(e.what());
    }
}

const Session &SessionManager::getActiveSession()
{
    return activeSession;
}

void SessionManager::addSnapshot(const Snapshot &snapshot)
{
    LOG_METHOD("cardId=" + uuids::to_string(snapshot.getCard().getId()));

    activeSession.addSnapshot(snapshot);
    sessionRepository->saveSession(activeSession);
}

std::list<Snapshot> SessionManager::getAllCardSnapshots(const Card &card)
{
    LOG_METHOD("cardId=" + uuids::to_string(card.getId()));

    std::list<Snapshot> result;

    for (auto session : sessionRepository->getSessions())
        for (auto snapshot : session)
            if (snapshot.getCard() == card)
                result.push_back(snapshot);

    return result;
}
