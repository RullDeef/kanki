#pragma once

#include "model/card.hpp"

class ILearner
{
public:
    virtual ~ILearner() = default;

    virtual Card getNextForLearn(size_t deckId) = 0;
    virtual Card getNextForRepeat(size_t deckId, int paramType) = 0;
};
