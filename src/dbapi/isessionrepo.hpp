#pragma once

#include <list>
#include "snapshotinfo.hpp"
#include "sessioninfo.hpp"

class ISessionRepository
{
public:
    virtual ~ISessionRepository() = default;

    virtual void saveSession(const SessionInfo& session) = 0;

    virtual SessionInfo getSessionById(size_t sessionId) = 0;
    virtual std::list<SnapshotInfo> getSnapshotsInSession(size_t sessionId) = 0;
};
