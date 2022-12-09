#pragma once

#include "model/snapshot.hpp"

class SnapshotBuilder
{
    using ParamType = Snapshot::ParamType;

public:
    SnapshotBuilder();
    static SnapshotBuilder random();
    static SnapshotBuilder random(Card card);

    SnapshotBuilder &withCard(Card newCard);
    SnapshotBuilder &withParamType(ParamType newParamType);
    SnapshotBuilder &withParamTypeNone();
    SnapshotBuilder &withParamTypeReading();
    SnapshotBuilder &withParamTypeTranslation();
    SnapshotBuilder &withKnowledgeDegree(int newDegree);
    SnapshotBuilder &withTimePoint(time_point newTimePoint);

    Snapshot build();

private:
    Card card;
    ParamType paramType;
    int knowledgeDegree;
    time_point timePoint;
};
