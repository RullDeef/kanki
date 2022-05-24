#pragma once

#include "model/snapshot.hpp"

class IEstimator
{
public:
    virtual ~IEstimator() = default;

    virtual void markEasy(Snapshot& snapshot) = 0;
    virtual void markGood(Snapshot& snapshot) = 0;
    virtual void markAgain(Snapshot& snapshot) = 0;
};
