#pragma once

#include <list>
#include <chrono>
#include "snapshot.hpp"

class Session
{
public:
    Session(size_t id = 0,
        std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now(),
        std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now())
        : id(id), startTime(startTime), endTime(endTime)
    {}

    size_t getId() const { return id; }

    size_t size() const { return snapshots.size(); }

    std::chrono::system_clock::time_point getStartTime() const { return startTime; }
    std::chrono::system_clock::time_point getEndTime() const { return endTime; }

    void endSession() { endTime = std::chrono::system_clock::now(); }

    void addSnapshot(const Snapshot& snapshot) { snapshots.push_back(snapshot); }

    std::list<Snapshot>::const_iterator begin() const { return snapshots.begin(); }
    std::list<Snapshot>::const_iterator end() const { return snapshots.end(); }

private:
    size_t id;
    std::list<Snapshot> snapshots;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
};
