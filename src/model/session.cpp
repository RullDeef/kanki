#include "session.hpp"

Session::Session(size_t id,
                 std::chrono::system_clock::time_point startTime,
                 std::chrono::system_clock::time_point endTime)
    : id(id), startTime(startTime), endTime(endTime)
{
}

size_t Session::getId() const
{
    return id;
}

size_t Session::size() const
{
    return snapshots.size();
}

std::chrono::system_clock::time_point Session::getStartTime() const
{
    return startTime;
}

std::chrono::system_clock::time_point Session::getEndTime() const
{
    return endTime;
}

void Session::endSession()
{
    endTime = std::chrono::system_clock::now();
}

void Session::addSnapshot(const Snapshot &snapshot)
{
    snapshots.push_back(snapshot);
}

std::list<Snapshot>::const_iterator Session::begin() const
{
    return snapshots.begin();
}

std::list<Snapshot>::const_iterator Session::end() const
{
    return snapshots.end();
}
