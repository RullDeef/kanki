#include "learneradapter.hpp"
#include "convertor.hpp"

LearnerViewAdapter::LearnerViewAdapter(UILearnerView &adaptee)
    : adaptee(adaptee)
{
}

void LearnerViewAdapter::showCard(const Card &card)
{
    auto params = ParamsConvertor().toCardParams(card);
    adaptee.showCard(params);
}

void LearnerViewAdapter::askCard(const Card &card, int paramType)
{
    auto params = ParamsConvertor().toCardParams(card);
    adaptee.askCard(params, paramType);
}

void LearnerViewAdapter::noCardsForLearn()
{
    adaptee.noCardsForLearn();
}

void LearnerViewAdapter::noCardsForRepeat()
{
    adaptee.noCardsForRepeat();
}
