#include "snapshot.hpp"

Snapshot::Snapshot(const Card &card, ParamType paramType, int knowledgeDegree, time_point timePoint)
    : card(card), paramType(paramType), knowledgeDegree(knowledgeDegree), timePoint(timePoint)
{
}

const Card &Snapshot::getCard() const
{
    return card;
}

Snapshot::ParamType Snapshot::getParamType() const
{
    return paramType;
}

int Snapshot::getKnowledgeDegree() const
{
    return knowledgeDegree;
}

void Snapshot::setKnowledgeDegree(int degree)
{
    knowledgeDegree = degree;
}

time_point Snapshot::getTimePoint() const
{
    return timePoint;
}

duration Snapshot::getTimeDelta() const
{
    return clock_spec::now() - timePoint;
}
