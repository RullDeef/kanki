#include <gtest/gtest.h>
#include "core/spacedestimator.hpp"
#include "builders/cardbuilder.hpp"
#include "builders/snapshotbuilder.hpp"

TEST(SpacedEstimator_markEasy, baseCase)
{
    auto snapshot = SnapshotBuilder::random()
                        .withKnowledgeDegree(3)
                        .build();

    SpacedEstimator estimator;

    estimator.markEasy(snapshot);

    ASSERT_EQ(snapshot.getKnowledgeDegree(), 5);
}

TEST(SpacedEstimator_markGood, baseCase)
{
    auto snapshot = SnapshotBuilder::random()
                        .withKnowledgeDegree(3)
                        .build();

    SpacedEstimator estimator;

    estimator.markGood(snapshot);

    ASSERT_EQ(snapshot.getKnowledgeDegree(), 4);
}

TEST(SpacedEstimator_markAgain, baseCase)
{
    auto snapshot = SnapshotBuilder::random()
                        .withKnowledgeDegree(3)
                        .build();

    SpacedEstimator estimator;

    estimator.markAgain(snapshot);

    ASSERT_EQ(snapshot.getKnowledgeDegree(), 0);
}
