#pragma once

#include <list>
#include "tools/time.hpp"
#include "snapshot.hpp"

class Session
{
public:
    using ConstIterator = std::list<Snapshot>::const_iterator;

    Session(size_t id = 0,
            time_point startTime = clock_spec::now(),
            time_point endTime = clock_spec::now());

    size_t getId() const;
    size_t size() const;
    time_point getStartTime() const;
    time_point getEndTime() const;

    void endSession();
    void addSnapshot(const Snapshot &snapshot);

    ConstIterator begin() const;
    ConstIterator end() const;

private:
    size_t id;
    std::list<Snapshot> snapshots;
    time_point startTime;
    time_point endTime;
};
