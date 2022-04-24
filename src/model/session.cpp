#include "session.hpp"

Session::Session()
    : startTime(std::chrono::system_clock::now())
{}

void Session::endSession()
{
    endTime = std::chrono::system_clock::now();
}

void Session::addSnapshot(const CardSnapshot& snapshot)
{
    snapshots.push_back(snapshot);
}

std::list<CardSnapshot>::const_iterator Session::begin() const
{
    return snapshots.begin();
}

std::list<CardSnapshot>::const_iterator Session::end() const
{
    return snapshots.end();
}
