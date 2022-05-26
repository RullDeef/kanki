#pragma once

#include <list>
#include <chrono>
#include "snapshot.hpp"

class Session
{
public:
    Session(size_t id = 0,
            std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now(),
            std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now());

    size_t getId() const;
    size_t size() const;
    std::chrono::system_clock::time_point getStartTime() const;
    std::chrono::system_clock::time_point getEndTime() const;

    void endSession();
    void addSnapshot(const Snapshot &snapshot);

    std::list<Snapshot>::const_iterator begin() const;
    std::list<Snapshot>::const_iterator end() const;

private:
    size_t id;
    std::list<Snapshot> snapshots;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
};
