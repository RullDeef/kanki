#pragma once

#include "card.hpp"

class CardSnapshot
{
public:
    enum class ParamType { READING, TRANSLATION };

    CardSnapshot(const Card& card, ParamType paramType, int knowledgeDegree);

private:
    Card card;
    ParamType paramType;
    int knowledgeDegree;
};
