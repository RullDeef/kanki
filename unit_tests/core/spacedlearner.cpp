#include <gtest/gtest.h>
#include "mock/collectionmanager.hpp"
#include "mock/sessionmanager.hpp"
#include "core/spacedlearner.hpp"

using ::testing::AtLeast;
using ::testing::Return;

TEST(SpacedLearner_getNextForLearn, EmptyDeck)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck emptyDeck(1, L"empty deck");

    EXPECT_CALL(collectionManager, getDeckById)
        .Times(1)
        .WillOnce(Return(emptyDeck));

    EXPECT_ANY_THROW(learner.getNextForLearn(1));
}

TEST(SpacedLearner_getNextForLearn, NoNewCards)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck oldDeck(3, L"old deck");
    oldDeck.addCard(Card(13));
    oldDeck.addCard(Card(14));
    oldDeck.addCard(Card(15));

    std::list<Snapshot> snapshots = {
        Snapshot(Card(13), Snapshot::ParamType::READING),
        Snapshot(Card(14), Snapshot::ParamType::READING),
        Snapshot(Card(15), Snapshot::ParamType::READING)};

    EXPECT_CALL(collectionManager, getDeckById)
        .Times(1)
        .WillOnce(Return(oldDeck));

    EXPECT_CALL(sessionManager, getAllCardSnapshots)
        .Times(3)
        .WillRepeatedly(Return(snapshots));

    EXPECT_ANY_THROW(learner.getNextForLearn(3));
}

TEST(SpacedLearner_getNextForLearn, AllCardsNew)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck newDeck(2, L"new deck");
    Card firstCard(10, L"first symbol", L"first reading", L"first description");
    newDeck.addCard(firstCard);
    newDeck.addCard(Card(11));
    newDeck.addCard(Card(12));

    EXPECT_CALL(collectionManager, getDeckById)
        .Times(1)
        .WillOnce(Return(newDeck));

    EXPECT_CALL(sessionManager, getAllCardSnapshots)
        .Times(1)
        .WillOnce(Return(std::list<Snapshot>()));

    auto card = learner.getNextForLearn(2);
    EXPECT_EQ(card, firstCard);
}

TEST(SpacedLearner_getNextForLearn, HasReadyForRepeat)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck freshDeck(4, L"fresh deck");
    Card lastCard(12);
    freshDeck.addCard(Card(10));
    freshDeck.addCard(Card(11));
    freshDeck.addCard(lastCard);

    auto tme = [](time_t t)
    { return clock_spec::from_time_t(t); };

    std::list<Snapshot> snapshots1 = {
        Snapshot(Card(10), Snapshot::ParamType::NONE, 0, tme(100)),
        Snapshot(Card(10), Snapshot::ParamType::READING, 1, tme(120)),
        Snapshot(Card(10), Snapshot::ParamType::TRANSLATION, 1, tme(150))};

    std::list<Snapshot> snapshots2 = {
        Snapshot(Card(11), Snapshot::ParamType::NONE, 0, tme(200)),
        Snapshot(Card(11), Snapshot::ParamType::READING, 1, tme(280)),
        Snapshot(Card(11), Snapshot::ParamType::READING, 3, tme(320))};

    std::list<Snapshot> snapshots3 = {};

    EXPECT_CALL(collectionManager, getDeckById)
        .WillOnce(Return(freshDeck));

    EXPECT_CALL(sessionManager, getAllCardSnapshots)
        .WillOnce(Return(snapshots1))
        .WillOnce(Return(snapshots2))
        .WillOnce(Return(snapshots3));

    auto card = learner.getNextForLearn(4);
    EXPECT_EQ(card, lastCard);
}

TEST(SpacedLearner_getNextForRepeat, EmptyDeck)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck emptyDeck(1, L"deck name");

    EXPECT_CALL(collectionManager, getDeckById)
        .WillOnce(Return(emptyDeck));

    EXPECT_ANY_THROW(learner.getNextForRepeat(1, Snapshot::ParamType::READING));
}

TEST(SpacedLearner_getNextForRepeat, AllNewCards)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck newDeck(2, L"new deck");
    newDeck.addCard(Card(10));
    newDeck.addCard(Card(11));
    newDeck.addCard(Card(12));

    EXPECT_CALL(collectionManager, getDeckById)
        .WillOnce(Return(newDeck));

    EXPECT_CALL(sessionManager, getAllCardSnapshots)
        .Times(3)
        .WillRepeatedly(Return(std::list<Snapshot>()));

    EXPECT_ANY_THROW(learner.getNextForRepeat(2, Snapshot::ParamType::READING));
}

TEST(SpacedLearner_getNextForRepeat, AllReadyCards)
{
    MockCollectionManager collectionManager;
    MockSessionManager sessionManager;
    SpacedLearner learner(&collectionManager, &sessionManager);

    Deck freshDeck(4, L"fresh deck");
    freshDeck.addCard(Card(10));
    freshDeck.addCard(Card(11));
    freshDeck.addCard(Card(12));

    auto tme = [](time_t t)
    { return clock_spec::from_time_t(t); };

    std::list<Snapshot> snapshots1 = {
        Snapshot(Card(10), Snapshot::ParamType::NONE, 0, tme(100)),
        Snapshot(Card(10), Snapshot::ParamType::READING, 1, tme(120)),
        Snapshot(Card(10), Snapshot::ParamType::TRANSLATION, 1, tme(150))};

    std::list<Snapshot> snapshots2 = {
        Snapshot(Card(11), Snapshot::ParamType::NONE, 0, tme(200)),
        Snapshot(Card(11), Snapshot::ParamType::READING, 1, tme(280)),
        Snapshot(Card(11), Snapshot::ParamType::READING, 3, tme(320))};

    std::list<Snapshot> snapshots3 = {
        Snapshot(Card(12), Snapshot::ParamType::NONE, 0, tme(400)),
        Snapshot(Card(12), Snapshot::ParamType::TRANSLATION, 2, tme(425)),
        Snapshot(Card(12), Snapshot::ParamType::TRANSLATION, 3, tme(480))};

    EXPECT_CALL(collectionManager, getDeckById)
        .WillOnce(Return(freshDeck));

    EXPECT_CALL(sessionManager, getAllCardSnapshots)
        .WillOnce(Return(snapshots1))
        .WillOnce(Return(snapshots2))
        .WillOnce(Return(snapshots3));

    auto card = learner.getNextForRepeat(4, Snapshot::ParamType::READING);
    EXPECT_EQ(card, Card(10));
}
