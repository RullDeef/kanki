#include "snapshotbuilder.hpp"
#include "cardbuilder.hpp"
#include "builder_base.hpp"

SnapshotBuilder::SnapshotBuilder()
    : card(CardBuilder::random().build())
{
}

SnapshotBuilder SnapshotBuilder::random()
{
    return random(CardBuilder::random().build());
}

SnapshotBuilder SnapshotBuilder::random(Card card)
{
    ParamType paramType = rand() % 2 == 1 ? ParamType::READING : ParamType::TRANSLATION;

    return SnapshotBuilder()
        .withCard(card)
        .withParamType(paramType)
        .withKnowledgeDegree(rand() % 100)
        .withTimePoint(gen_random_time_point(-10, 10));
}

SnapshotBuilder &SnapshotBuilder::withCard(Card newCard)
{
    card = newCard;
    return *this;
}

SnapshotBuilder &SnapshotBuilder::withParamType(ParamType newParamType)
{
    paramType = newParamType;
    return *this;
}

SnapshotBuilder &SnapshotBuilder::withParamTypeNone()
{
    return withParamType(ParamType::NONE);
}

SnapshotBuilder &SnapshotBuilder::withParamTypeReading()
{
    return withParamType(ParamType::READING);
}

SnapshotBuilder &SnapshotBuilder::withParamTypeTranslation()
{
    return withParamType(ParamType::TRANSLATION);
}

SnapshotBuilder &SnapshotBuilder::withKnowledgeDegree(int newDegree)
{
    knowledgeDegree = newDegree;
    return *this;
}

SnapshotBuilder &SnapshotBuilder::withTimePoint(time_point newTimePoint)
{
    timePoint = newTimePoint;
    return *this;
}

Snapshot SnapshotBuilder::build()
{
    return Snapshot(card, paramType, knowledgeDegree, timePoint);
}
