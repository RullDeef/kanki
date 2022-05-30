#pragma once

#include "cardparams.hpp"
#include "deckparams.hpp"
#include "collectionparams.hpp"

class UILearnerView
{
public:
    virtual ~UILearnerView() = default;

    virtual void showCard(const CardParams& params) = 0;
    virtual void askCard(const CardParams& card, int paramType) = 0;

    virtual void noCardsForLearn() = 0;
    virtual void noCardsForRepeat() = 0;
};
