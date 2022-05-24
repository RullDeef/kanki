#pragma once

#include "model/card.hpp"
#include "model/snapshot.hpp"

class ILearner
{
public:
    virtual ~ILearner() = default;

    virtual Card getNextForLearn(size_t deckId) = 0;
    virtual Card getNextForRepeat(size_t deckId) = 0;
};
