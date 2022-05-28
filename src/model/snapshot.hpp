#pragma once

#include "tools/time.hpp"
#include "card.hpp"

class Snapshot
{
public:
    enum ParamType
    {
        NONE = 0,
        READING = 1,
        TRANSLATION = 2,
    };

    Snapshot(const Card &card,
             ParamType paramType = ParamType::NONE,
             int knowledgeDegree = 0,
             time_point timePoint = clock_spec::now());

    const Card &getCard() const;
    ParamType getParamType() const;
    int getKnowledgeDegree() const;

    void setKnowledgeDegree(int degree);

    time_point getTimePoint() const;

    // returns duration from creation time till now
    duration getTimeDelta() const;

private:
    Card card;
    ParamType paramType;
    int knowledgeDegree;
    time_point timePoint;
};
