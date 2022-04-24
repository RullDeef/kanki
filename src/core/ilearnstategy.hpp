#pragma once

#include "model/deck.hpp"
#include "model/cardsnapshot.hpp"

class ILearningStrategy
{
public:
    virtual ~ILearningStrategy() = default;

    virtual CardSnapshot getNextForLearn(const Deck& deck) = 0;
    virtual CardSnapshot getNextForRepeat(const Deck& deck) = 0;
};
