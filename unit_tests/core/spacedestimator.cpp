#include <gtest/gtest.h>
#include "core/spacedestimator.hpp"

TEST(SpacedEstimator_markEasy, baseCase)
{
    SpacedEstimator estimator;
    Card card(10);
    Snapshot snapshot(card, Snapshot::ParamType::READING, 3);

    estimator.markEasy(snapshot);

    ASSERT_EQ(snapshot.getKnowledgeDegree(), 5);
}

TEST(SpacedEstimator_markGood, baseCase)
{
    SpacedEstimator estimator;
    Card card(10);
    Snapshot snapshot(card, Snapshot::ParamType::READING, 3);

    estimator.markGood(snapshot);

    ASSERT_EQ(snapshot.getKnowledgeDegree(), 4);
}

TEST(SpacedEstimator_markAgain, baseCase)
{
    SpacedEstimator estimator;
    Card card(10);
    Snapshot snapshot(card, Snapshot::ParamType::READING, 3);

    estimator.markAgain(snapshot);

    ASSERT_EQ(snapshot.getKnowledgeDegree(), 0);
}
