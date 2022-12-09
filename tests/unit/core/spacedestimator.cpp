#include <gtest/gtest.h>
#include "core/spacedestimator.hpp"

static UUID getId(uint8_t index)
{
    std::array<uint8_t, 16> id10value = {
        0x00, 0x00, 0x00, index,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    return id10value;
}

TEST(SpacedEstimator_markEasy, baseCase)
{
    UUID id10 = getId(10);

    SpacedEstimator estimator;
    Card card(id10, L"symbol", L"reading", L"description");
    Snapshot snapshot(card, Snapshot::ParamType::READING, 3);

    estimator.markEasy(snapshot);

    ASSERT_EQ(snapshot.getKnowledgeDegree(), 5);
}

TEST(SpacedEstimator_markGood, baseCase)
{
    UUID id10 = getId(10);

    SpacedEstimator estimator;
    Card card(id10, L"symbol", L"reading", L"description");
    Snapshot snapshot(card, Snapshot::ParamType::READING, 3);

    estimator.markGood(snapshot);

    ASSERT_EQ(snapshot.getKnowledgeDegree(), 4);
}

TEST(SpacedEstimator_markAgain, baseCase)
{
    UUID id10 = getId(10);

    SpacedEstimator estimator;
    Card card(id10, L"symbol", L"reading", L"description");
    Snapshot snapshot(card, Snapshot::ParamType::READING, 3);

    estimator.markAgain(snapshot);

    ASSERT_EQ(snapshot.getKnowledgeDegree(), 0);
}
