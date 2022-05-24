#include "snapshot.hpp"

Snapshot::Snapshot(const Card& card, ParamType paramType, int knowledgeDegree,
        std::chrono::system_clock::time_point timePoint)
    : card(card), paramType(paramType), knowledgeDegree(knowledgeDegree), timePoint(timePoint)
{}

const Card& Snapshot::getCard() const
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

std::chrono::system_clock::time_point Snapshot::getTimePoint() const
{
    return timePoint;
}

std::chrono::system_clock::duration Snapshot::getTimeDelta() const
{
    return std::chrono::system_clock::now() - timePoint;
}
