#pragma once

#include "model/card.hpp"
#include "model/snapshot.hpp"

class ILearnerView
{
public:
    virtual ~ILearnerView() = default;

    virtual void showCard(const Card& card) = 0;
    virtual void askCard(const Card& card) = 0;
    
    virtual void noCardsForLearn() = 0;
    virtual void noCardsForRepeat() = 0;
};
