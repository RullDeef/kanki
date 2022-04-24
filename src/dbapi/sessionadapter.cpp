#include "sessionadapter.hpp"

SessionAdapter::SessionAdapter(std::shared_ptr<ISessionRepository> repository)
    : repository(repository)
{}

Session SessionAdapter::extractSession(size_t sessionId)
{
    auto session = Session();

    auto snapshots = repository->getSnapshotsInSession(sessionId);
    for (const auto& snapshot : snapshots)
    {
        session.addSnapshot();
    }

    return std::move(session);
}
