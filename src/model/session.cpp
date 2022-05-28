#include "session.hpp"

Session::Session(size_t id, time_point startTime, time_point endTime)
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

time_point Session::getStartTime() const
{
    return startTime;
}

time_point Session::getEndTime() const
{
    return endTime;
}

void Session::endSession()
{
    endTime = clock_spec::now();
}

void Session::addSnapshot(const Snapshot &snapshot)
{
    snapshots.push_back(snapshot);
}

Session::ConstIterator Session::begin() const
{
    return snapshots.begin();
}

Session::ConstIterator Session::end() const
{
    return snapshots.end();
}
