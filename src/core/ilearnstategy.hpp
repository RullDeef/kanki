#pragma once

#include "model/deck.hpp"
#include "model/cardsnapshot.hpp"

class ILearningStrategy
{
public:
    virtual ~ILearningStrategy() = default;

    virtual Card getNextForLearn(const Deck& deck) = 0;
    virtual CardSnapshot getNextForRepeat(const Deck& deck, CardSnapshot::ParamType param) = 0;
};
