#pragma once

#include <list>
#include <chrono>
#include "cardsnapshot.hpp"

class Session
{
public:
    Session();

    void endSession();

    void addSnapshot(const CardSnapshot& snapshot);

    std::list<CardSnapshot>::const_iterator begin() const;
    std::list<CardSnapshot>::const_iterator end() const;

private:
    std::list<CardSnapshot> snapshots;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
};
