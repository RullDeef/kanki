#pragma once

#include "model/card.hpp"

class ILearner
{
public:
    virtual ~ILearner() = default;

    virtual Card getNextForLearn(UUID deckId) = 0;
    virtual Card getNextForRepeat(UUID deckId, int paramType) = 0;
};
