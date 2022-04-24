#pragma once

#include "model/cardsnapshot.hpp"

class IEstimatorStrategy
{
public:
    virtual ~IEstimatorStrategy() = default;

    virtual void markEasy(const CardSnapshot& snapshot) = 0;
    virtual void markGood(const CardSnapshot& snapshot) = 0;
    virtual void markAgain(const CardSnapshot& snapshot) = 0;
};
