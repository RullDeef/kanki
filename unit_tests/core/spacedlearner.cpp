#include <gtest/gtest.h>
#include "mock/core/collectionmanager.hpp"
#include "mock/core/sessionmanager.hpp"
#include "core/spacedlearner.hpp"

using ::testing::AtLeast;
using ::testing::Return;

static UUID getId(uint8_t index)
{
    std::array<uint8_t, 16> id10value = {
        0x00, 0x00, 0x00, index,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    return id10value;
}

TEST(SpacedLearner_getNextForLearn, EmptyDeck)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck emptyDeck(getId(1), L"empty deck");

    EXPECT_CALL(collectionManager, getDeckById)
        .Times(1)
        .WillOnce(Return(emptyDeck));

    EXPECT_ANY_THROW(learner.getNextForLearn(getId(1)));
}

TEST(SpacedLearner_getNextForLearn, NoNewCards)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck oldDeck(getId(3), L"old deck");
    oldDeck.addCard(Card(getId(13), L"symbol", L"reading", L"description"));
    oldDeck.addCard(Card(getId(14), L"symbol", L"reading", L"description"));
    oldDeck.addCard(Card(getId(15), L"symbol", L"reading", L"description"));

    std::list<Snapshot> snapshots = {
        Snapshot(Card(getId(13), L"symbol", L"reading", L"description"), Snapshot::ParamType::READING),
        Snapshot(Card(getId(14), L"symbol", L"reading", L"description"), Snapshot::ParamType::READING),
        Snapshot(Card(getId(15), L"symbol", L"reading", L"description"), Snapshot::ParamType::READING)};

    EXPECT_CALL(collectionManager, getDeckById)
        .Times(1)
        .WillOnce(Return(oldDeck));

    EXPECT_CALL(sessionManager, getAllCardSnapshots)
        .Times(3)
        .WillRepeatedly(Return(snapshots));

    EXPECT_ANY_THROW(learner.getNextForLearn(getId(3)));
}

TEST(SpacedLearner_getNextForLearn, AllCardsNew)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck newDeck(getId(2), L"new deck");
    Card firstCard(getId(10), L"first symbol", L"first reading", L"first description");
    newDeck.addCard(firstCard);
    newDeck.addCard(Card(getId(11), L"symbol", L"reading", L"description"));
    newDeck.addCard(Card(getId(12), L"symbol", L"reading", L"description"));

    EXPECT_CALL(collectionManager, getDeckById)
        .Times(1)
        .WillOnce(Return(newDeck));

    EXPECT_CALL(sessionManager, getAllCardSnapshots)
        .Times(1)
        .WillOnce(Return(std::list<Snapshot>()));

    auto card = learner.getNextForLearn(getId(2));
    EXPECT_EQ(card, firstCard);
}

TEST(SpacedLearner_getNextForLearn, HasReadyForRepeat)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck freshDeck(getId(4), L"fresh deck");
    Card lastCard(getId(12), L"last symbol", L"last reading", L"last description");
    freshDeck.addCard(Card(getId(10), L"symbol", L"reading", L"description"));
    freshDeck.addCard(Card(getId(11), L"symbol", L"reading", L"description"));
    freshDeck.addCard(lastCard);

    auto tme = [](time_t t)
    { return clock_spec::from_time_t(t); };

    std::list<Snapshot> snapshots1 = {
        Snapshot(Card(getId(10), L"symbol", L"reading", L"description"), Snapshot::ParamType::NONE, 0, tme(100)),
        Snapshot(Card(getId(10), L"symbol", L"reading", L"description"), Snapshot::ParamType::READING, 1, tme(120)),
        Snapshot(Card(getId(10), L"symbol", L"reading", L"description"), Snapshot::ParamType::TRANSLATION, 1, tme(150))};

    std::list<Snapshot> snapshots2 = {
        Snapshot(Card(getId(11), L"symbol", L"reading", L"description"), Snapshot::ParamType::NONE, 0, tme(200)),
        Snapshot(Card(getId(11), L"symbol", L"reading", L"description"), Snapshot::ParamType::READING, 1, tme(280)),
        Snapshot(Card(getId(11), L"symbol", L"reading", L"description"), Snapshot::ParamType::READING, 3, tme(320))};

    std::list<Snapshot> snapshots3 = {};

    EXPECT_CALL(collectionManager, getDeckById)
        .WillOnce(Return(freshDeck));

    EXPECT_CALL(sessionManager, getAllCardSnapshots)
        .WillOnce(Return(snapshots1))
        .WillOnce(Return(snapshots2))
        .WillOnce(Return(snapshots3));

    auto card = learner.getNextForLearn(getId(4));
    EXPECT_EQ(card, lastCard);
}

TEST(SpacedLearner_getNextForRepeat, EmptyDeck)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck emptyDeck(getId(1), L"deck name");

    EXPECT_CALL(collectionManager, getDeckById)
        .WillOnce(Return(emptyDeck));

    EXPECT_ANY_THROW(learner.getNextForRepeat(getId(1), Snapshot::ParamType::READING));
}

TEST(SpacedLearner_getNextForRepeat, AllNewCards)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck newDeck(getId(2), L"new deck");
    newDeck.addCard(Card(getId(10), L"symbol", L"reading", L"description"));
    newDeck.addCard(Card(getId(11), L"symbol", L"reading", L"description"));
    newDeck.addCard(Card(getId(12), L"symbol", L"reading", L"description"));

    EXPECT_CALL(collectionManager, getDeckById)
        .WillOnce(Return(newDeck));

    EXPECT_CALL(sessionManager, getAllCardSnapshots)
        .Times(3)
        .WillRepeatedly(Return(std::list<Snapshot>()));

    EXPECT_ANY_THROW(learner.getNextForRepeat(getId(2), Snapshot::ParamType::READING));
}

TEST(SpacedLearner_getNextForRepeat, AllReadyCards)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck freshDeck(getId(4), L"fresh deck");
    freshDeck.addCard(Card(getId(10), L"symbol", L"reading", L"description"));
    freshDeck.addCard(Card(getId(11), L"symbol", L"reading", L"description"));
    freshDeck.addCard(Card(getId(12), L"symbol", L"reading", L"description"));

    auto tme = [](time_t t)
    { return clock_spec::from_time_t(t); };

    std::list<Snapshot> snapshots1 = {
        Snapshot(Card(getId(10), L"symbol", L"reading", L"description"), Snapshot::ParamType::NONE, 0, tme(100)),
        Snapshot(Card(getId(10), L"symbol", L"reading", L"description"), Snapshot::ParamType::READING, 1, tme(120)),
        Snapshot(Card(getId(10), L"symbol", L"reading", L"description"), Snapshot::ParamType::TRANSLATION, 1, tme(150))};

    std::list<Snapshot> snapshots2 = {
        Snapshot(Card(getId(11), L"symbol", L"reading", L"description"), Snapshot::ParamType::NONE, 0, tme(200)),
        Snapshot(Card(getId(11), L"symbol", L"reading", L"description"), Snapshot::ParamType::READING, 1, tme(280)),
        Snapshot(Card(getId(11), L"symbol", L"reading", L"description"), Snapshot::ParamType::READING, 3, tme(320))};

    std::list<Snapshot> snapshots3 = {
        Snapshot(Card(getId(12), L"symbol", L"reading", L"description"), Snapshot::ParamType::NONE, 0, tme(400)),
        Snapshot(Card(getId(12), L"symbol", L"reading", L"description"), Snapshot::ParamType::TRANSLATION, 2, tme(425)),
        Snapshot(Card(getId(12), L"symbol", L"reading", L"description"), Snapshot::ParamType::TRANSLATION, 3, tme(480))};

    EXPECT_CALL(collectionManager, getDeckById)
        .WillOnce(Return(freshDeck));

    EXPECT_CALL(sessionManager, getAllCardSnapshots)
        .WillOnce(Return(snapshots1))
        .WillOnce(Return(snapshots2))
        .WillOnce(Return(snapshots3));

    auto card = learner.getNextForRepeat(getId(4), Snapshot::ParamType::READING);
    EXPECT_EQ(card, Card(getId(10), L"symbol", L"reading", L"description"));
}
