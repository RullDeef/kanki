#pragma once

#include <chrono>
#include "card.hpp"

class Snapshot
{
public:
    enum class ParamType { READING, TRANSLATION };

    ///TODO: add time point to snapshot
    Snapshot(const Card& card, ParamType paramType, int knowledgeDegree = 0,
        std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::now());

    const Card& getCard() const;
    ParamType getParamType() const;
    int getKnowledgeDegree() const;

    // возвращает время с момента создания снапшота
    std::chrono::system_clock::duration getTimeDelta() const;

private:
    Card card;
    ParamType paramType;
    int knowledgeDegree;

    std::chrono::system_clock::time_point timePoint;
};