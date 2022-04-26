#include "cardsnapshot.hpp"

CardSnapshot::CardSnapshot(const Card& card, ParamType paramType, int knowledgeDegree,
        std::chrono::system_clock::time_point timePoint)
    : card(card), paramType(paramType), knowledgeDegree(knowledgeDegree), timePoint(timePoint)
{}

CardSnapshot::ParamType CardSnapshot::getParamType() const
{
    return paramType;
}

int CardSnapshot::getKnowledgeDegree() const
{
    return knowledgeDegree;
}

std::chrono::system_clock::duration CardSnapshot::getTimeDelta() const
{
    return std::chrono::system_clock::now() - timePoint;
}
