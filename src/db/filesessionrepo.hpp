#pragma once

#include <string>
#include <list>
#include <map>
#include "dbapi/snapshotinfo.hpp"
#include "dbapi/isessionrepo.hpp"

class FileSessionRepository : public ISessionRepository
{
public:
    explicit FileSessionRepository(const std::string& filename);

    virtual void saveSession(const SessionInfo& session) override;

    virtual SessionInfo getSessionById(size_t sessionId) override;
    virtual std::list<SnapshotInfo> getSnapshotsInSession(size_t sessionId) override;

private:
    std::string filename;

    std::map<size_t, SessionInfo> sessions;
    std::map<size_t, SnapshotInfo> snapshots;
};
