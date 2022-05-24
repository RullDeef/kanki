#pragma once

#include <list>
#include <chrono>
#include "snapshot.hpp"

class Session
{
public:
    Session(size_t id = 0)
        : id(id), startTime(std::chrono::system_clock::now())
    {}

    size_t getId() const { return id; }

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
