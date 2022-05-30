#pragma once

#include "core/ilearnerview.hpp"
#include "uilearnerview.hpp"

class LearnerViewAdapter : public ILearnerView
{
public:
    LearnerViewAdapter(UILearnerView &adaptee);

    virtual void showCard(const Card &card) override;
    virtual void askCard(const Card &card, int paramType) override;

    virtual void noCardsForLearn() override;
    virtual void noCardsForRepeat() override;

private:
    UILearnerView &adaptee;
};
