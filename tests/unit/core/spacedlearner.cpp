#include <gtest/gtest.h>
#include "spacedlearner_fixture.hpp"
#include "builders/builder_base.hpp"
#include "builders/cardbuilder.hpp"
#include "builders/deckbuilder.hpp"
#include "builders/snapshotbuilder.hpp"

using ::testing::Return;

TEST_F(SpacedLearnerFixture, SpacedLearner_getNextForLearn_emptyDeck)
{
    auto deck = DeckBuilder::random(0).build();

    EXPECT_CALL(*collectionManager, getDeckById)
        .WillOnce(Return(deck));

    EXPECT_ANY_THROW(learner.getNextForLearn(deck.getId()));
}

TEST_F(SpacedLearnerFixture, SpacedLearner_getNextForLearn_noNewCards)
{
    Card cards[] = {
        CardBuilder::random().build(),
        CardBuilder::random().build(),
        CardBuilder::random().build(),
    };

    auto deck = DeckBuilder::random(0)
                    .withCards({cards[0], cards[1], cards[2]})
                    .build();

    std::list<Snapshot> snapshots = {
        SnapshotBuilder::random(cards[0]).withParamTypeReading().build(),
        SnapshotBuilder::random(cards[1]).withParamTypeReading().build(),
        SnapshotBuilder::random(cards[2]).withParamTypeReading().build(),
    };

    EXPECT_CALL(*collectionManager, getDeckById)
        .WillOnce(Return(deck));

    EXPECT_CALL(*sessionManager, getAllCardSnapshots)
        .Times(3)
        .WillRepeatedly(Return(snapshots));

    EXPECT_ANY_THROW(learner.getNextForLearn(deck.getId()));
}

TEST_F(SpacedLearnerFixture, SpacedLearner_getNextForLearn_allCardsNew)
{
    auto firstCard = CardBuilder::random().build();
    auto deck = DeckBuilder::random()
                    .withCards({
                        firstCard,
                        CardBuilder::random().build(),
                        CardBuilder::random().build(),
                    })
                    .build();

    EXPECT_CALL(*collectionManager, getDeckById)
        .WillOnce(Return(deck));

    EXPECT_CALL(*sessionManager, getAllCardSnapshots)
        .WillOnce(Return(std::list<Snapshot>()));

    auto card = learner.getNextForLearn(deck.getId());
    EXPECT_EQ(card, firstCard);
}

TEST_F(SpacedLearnerFixture, SpacedLearner_getNextForLearn_hasReadyForRepeat)
{
    Card cards[] = {
        CardBuilder::random().build(),
        CardBuilder::random().build(),
        CardBuilder::random().build(),
    };

    auto deck = DeckBuilder::random()
                    .withCards({cards[0], cards[1], cards[2]})
                    .build();

    auto snapshots_1 = std::list{
        SnapshotBuilder::random(cards[0])
            .withTimePoint(gen_random_time_point(-3, -2))
            .withParamTypeNone()
            .withKnowledgeDegree(0)
            .build(),
        SnapshotBuilder::random(cards[0])
            .withTimePoint(gen_random_time_point(-2, -1))
            .withParamTypeReading()
            .withKnowledgeDegree(1)
            .build(),
        SnapshotBuilder::random(cards[0])
            .withTimePoint(gen_random_time_point(-1, 0))
            .withParamTypeTranslation()
            .withKnowledgeDegree(1)
            .build(),
    };

    auto snapshots_2 = std::list{
        SnapshotBuilder::random(cards[1])
            .withTimePoint(gen_random_time_point(-3, -2))
            .withParamTypeNone()
            .withKnowledgeDegree(0)
            .build(),
        SnapshotBuilder::random(cards[1])
            .withTimePoint(gen_random_time_point(-2, -1))
            .withParamTypeReading()
            .withKnowledgeDegree(1)
            .build(),
        SnapshotBuilder::random(cards[1])
            .withTimePoint(gen_random_time_point(-1, 0))
            .withParamTypeReading()
            .withKnowledgeDegree(3)
            .build(),
    };

    EXPECT_CALL(*collectionManager, getDeckById)
        .WillOnce(Return(deck));

    EXPECT_CALL(*sessionManager, getAllCardSnapshots)
        .WillOnce(Return(snapshots_1))
        .WillOnce(Return(snapshots_2))
        .WillOnce(Return(std::list<Snapshot>()));

    auto card = learner.getNextForLearn(deck.getId());
    EXPECT_EQ(card, cards[2]);
}

TEST_F(SpacedLearnerFixture, SpacedLearner_getNextForRepeat_emptyDeck)
{
    auto deck = DeckBuilder::random().build();

    EXPECT_CALL(*collectionManager, getDeckById)
        .WillOnce(Return(deck));

    EXPECT_ANY_THROW(learner.getNextForRepeat(deck.getId(), Snapshot::ParamType::READING));
}

TEST_F(SpacedLearnerFixture, SpacedLearner_getNextForRepeat_allNewCards)
{
    auto deck = DeckBuilder::random(3).build();

    EXPECT_CALL(*collectionManager, getDeckById)
        .WillOnce(Return(deck));

    EXPECT_CALL(*sessionManager, getAllCardSnapshots)
        .Times(3)
        .WillRepeatedly(Return(std::list<Snapshot>()));

    EXPECT_ANY_THROW(learner.getNextForRepeat(deck.getId(), Snapshot::ParamType::READING));
}

TEST_F(SpacedLearnerFixture, SpacedLearner_getNextForRepeat_allReadyCards)
{
    Card cards[] = {
        CardBuilder::random().build(),
        CardBuilder::random().build(),
        CardBuilder::random().build(),
    };

    auto deck = DeckBuilder::random()
                    .withCards({cards[0], cards[1], cards[2]})
                    .build();

    auto snapshots_1 = std::list{
        SnapshotBuilder::random(cards[0])
            .withParamTypeNone()
            .withKnowledgeDegree(0)
            .withTimePoint(gen_random_time_point(-10, -9))
            .build(),
        SnapshotBuilder::random(cards[0])
            .withParamTypeReading()
            .withKnowledgeDegree(1)
            .withTimePoint(gen_random_time_point(-9, -8))
            .build(),
        SnapshotBuilder::random(cards[0])
            .withParamTypeTranslation()
            .withKnowledgeDegree(1)
            .withTimePoint(gen_random_time_point(-8, -7))
            .build(),
    };

    auto snapshots_2 = std::list{
        SnapshotBuilder::random(cards[1])
            .withParamTypeNone()
            .withKnowledgeDegree(0)
            .withTimePoint(gen_random_time_point(-7, -6))
            .build(),
        SnapshotBuilder::random(cards[1])
            .withParamTypeReading()
            .withKnowledgeDegree(1)
            .withTimePoint(gen_random_time_point(-6, -5))
            .build(),
        SnapshotBuilder::random(cards[1])
            .withParamTypeReading()
            .withKnowledgeDegree(3)
            .withTimePoint(gen_random_time_point(-5, -4))
            .build(),
    };

    auto snapshots_3 = std::list{
        SnapshotBuilder::random(cards[2])
            .withParamTypeNone()
            .withKnowledgeDegree(0)
            .withTimePoint(gen_random_time_point(-4, -3))
            .build(),
        SnapshotBuilder::random(cards[2])
            .withParamTypeTranslation()
            .withKnowledgeDegree(2)
            .withTimePoint(gen_random_time_point(-3, -2))
            .build(),
        SnapshotBuilder::random(cards[2])
            .withParamTypeTranslation()
            .withKnowledgeDegree(3)
            .withTimePoint(gen_random_time_point(-2, -1))
            .build(),
    };

    EXPECT_CALL(*collectionManager, getDeckById)
        .WillOnce(Return(deck));

    EXPECT_CALL(*sessionManager, getAllCardSnapshots)
        .WillOnce(Return(snapshots_1))
        .WillOnce(Return(snapshots_2))
        .WillOnce(Return(snapshots_3));

    auto card = learner.getNextForRepeat(deck.getId(), Snapshot::ParamType::READING);

    EXPECT_EQ(card, cards[0]);
}
