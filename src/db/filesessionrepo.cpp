#include "filesessionrepo.hpp"

FileSessionRepository::FileSessionRepository(const std::string& filename)
    : filename(filename)
{}

void FileSessionRepository::saveSession(const SessionInfo& session)
{
}

SessionInfo FileSessionRepository::getSessionById(size_t sessionId)
{
    SessionInfo info;
    info.id = 0;
    info.startTime = 100;
    info.endTime = -1;
    return info;
}

std::list<SnapshotInfo> FileSessionRepository::getSnapshotsInSession(size_t sessionId)
{
    return {};
}
