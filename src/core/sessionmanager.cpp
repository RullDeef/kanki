#include "tools/logger.hpp"
#include "tools/idgenerator.hpp"
#include "sessionmanager.hpp"

SessionManager::SessionManager(ISessionRepository *sessionRepository)
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
    LOG_METHOD();

    activeSession.addSnapshot(snapshot);

    /// KOSTYLI: preserve active session in repository
    activeSession.endSession();
    sessionRepository->saveSession(activeSession);
}

std::list<Snapshot> SessionManager::getAllCardSnapshots(const Card &card)
{
    LOG_METHOD();

    std::list<Snapshot> result;

    for (auto session : sessionRepository->getSessions())
        for (auto snapshot : session)
            if (snapshot.getCard() == card)
                result.push_back(snapshot);

    return result;
}
