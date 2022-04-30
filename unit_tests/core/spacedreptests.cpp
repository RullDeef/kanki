#include <gtest/gtest.h>
#include "core/spacedrepetionlearn.hpp"
#include "mockmodelmanager.hpp"

using ::testing::AtLeast;
using ::testing::Return;

TEST(SpacedRepetitionLearn_getNextForLearn, EmptyDeck)
{
    std::shared_ptr<IModelManager> modelManager = std::shared_ptr<IModelManager>(new MockModelManager);
    MockModelManager& mockModelManager = *dynamic_cast<MockModelManager*>(modelManager.get());
    SpacedRepetitionLearn learner(modelManager);
    Deck emptyDeck;

    EXPECT_ANY_THROW(learner.getNextForLearn(emptyDeck));
}

TEST(SpacedRepetitionLearn_getNextForLearn, NoNewCards)
{
    std::shared_ptr<IModelManager> modelManager = std::shared_ptr<IModelManager>(new MockModelManager);
    MockModelManager& mockModelManager = *dynamic_cast<MockModelManager*>(modelManager.get());
    SpacedRepetitionLearn learner(modelManager);

    Deck deck;
    auto card1 = deck.addNewCard();
    auto card2 = deck.addNewCard();
    auto card3 = deck.addNewCard();

    *card1 = Card(L"card1", L"card1", L"card1");
    *card2 = Card(L"card2", L"card2", L"card2");
    *card3 = Card(L"card3", L"card3", L"card3");

    EXPECT_CALL(mockModelManager, getSnapshots)
        .Times(3)
        .WillOnce(Return(std::list<CardSnapshot>{CardSnapshot(*card1, CardSnapshot::ParamType::READING)}))
        .WillOnce(Return(std::list<CardSnapshot>{CardSnapshot(*card2, CardSnapshot::ParamType::READING)}))
        .WillOnce(Return(std::list<CardSnapshot>{CardSnapshot(*card3, CardSnapshot::ParamType::READING)}));

    EXPECT_ANY_THROW(learner.getNextForLearn(deck));
}

TEST(SpacedRepetitionLearn_getNextForLearn, AllCardsNew)
{
    std::shared_ptr<IModelManager> modelManager = std::shared_ptr<IModelManager>(new MockModelManager);
    MockModelManager& mockModelManager = *dynamic_cast<MockModelManager*>(modelManager.get());
    SpacedRepetitionLearn learner(modelManager);

    Deck deck;
    auto card1 = deck.addNewCard();
    auto card2 = deck.addNewCard();
    auto card3 = deck.addNewCard();

    *card1 = Card(L"card1", L"card1", L"card1");
    *card2 = Card(L"card2", L"card2", L"card2");
    *card3 = Card(L"card3", L"card3", L"card3");

    EXPECT_CALL(mockModelManager, getSnapshots)
        .Times(1)
        .WillOnce(Return(std::list<CardSnapshot>{}));
    
    auto card = learner.getNextForLearn(deck);
    EXPECT_EQ(card, *card1);
}

TEST(SpacedRepetitionLearn_getNextForLearn, HasReadyForRepeat)
{
    std::shared_ptr<IModelManager> modelManager = std::shared_ptr<IModelManager>(new MockModelManager);
    MockModelManager& mockModelManager = *dynamic_cast<MockModelManager*>(modelManager.get());
    SpacedRepetitionLearn learner(modelManager);

    Deck deck;
    auto card1 = deck.addNewCard();
    auto card2 = deck.addNewCard();
    auto card3 = deck.addNewCard();

    *card1 = Card(L"card1", L"card1", L"card1");
    *card2 = Card(L"card2", L"card2", L"card2");
    *card3 = Card(L"card3", L"card3", L"card3");

    EXPECT_CALL(mockModelManager, getSnapshots)
        .Times(3)
        .WillOnce(Return(std::list<CardSnapshot>{CardSnapshot(*card1, CardSnapshot::ParamType::READING)}))
        .WillOnce(Return(std::list<CardSnapshot>{CardSnapshot(*card2, CardSnapshot::ParamType::TRANSLATION)}))
        .WillOnce(Return(std::list<CardSnapshot>{}));

    auto card = learner.getNextForLearn(deck);
    EXPECT_EQ(card, *card3);
}

TEST(SpacedRepetitionLearn_getNextForRepeat, EmptyDeck)
{
    std::shared_ptr<IModelManager> modelManager = std::shared_ptr<IModelManager>(new MockModelManager);
    MockModelManager& mockModelManager = *dynamic_cast<MockModelManager*>(modelManager.get());
    SpacedRepetitionLearn learner(modelManager);
    Deck emptyDeck;

    EXPECT_ANY_THROW(learner.getNextForRepeat(emptyDeck, CardSnapshot::ParamType::READING));
}

TEST(SpacedRepetitionLearn_getNextForRepeat, AllNewCards)
{
    std::shared_ptr<IModelManager> modelManager = std::shared_ptr<IModelManager>(new MockModelManager);
    MockModelManager& mockModelManager = *dynamic_cast<MockModelManager*>(modelManager.get());
    SpacedRepetitionLearn learner(modelManager);

    Deck deck;
    auto card1 = deck.addNewCard();
    auto card2 = deck.addNewCard();
    auto card3 = deck.addNewCard();

    *card1 = Card(L"card1", L"card1", L"card1");
    *card2 = Card(L"card2", L"card2", L"card2");
    *card3 = Card(L"card3", L"card3", L"card3");

    EXPECT_CALL(mockModelManager, getSnapshots)
        .Times(3)
        .WillRepeatedly(Return(std::list<CardSnapshot>{}));

    EXPECT_ANY_THROW(learner.getNextForRepeat(deck, CardSnapshot::ParamType::READING));
}

TEST(SpacedRepetitionLearn_getNextForRepeat, AllReadyCards)
{
    std::shared_ptr<IModelManager> modelManager = std::shared_ptr<IModelManager>(new MockModelManager);
    MockModelManager& mockModelManager = *dynamic_cast<MockModelManager*>(modelManager.get());
    SpacedRepetitionLearn learner(modelManager);

    Deck deck;
    auto card1 = deck.addNewCard();
    auto card2 = deck.addNewCard();
    auto card3 = deck.addNewCard();

    *card1 = Card(L"card1", L"card1", L"card1");
    *card2 = Card(L"card2", L"card2", L"card2");
    *card3 = Card(L"card3", L"card3", L"card3");

    EXPECT_CALL(mockModelManager, getSnapshots)
        .Times(3)
        .WillOnce(Return(std::list<CardSnapshot>{CardSnapshot(*card1, CardSnapshot::ParamType::TRANSLATION)}))
        .WillOnce(Return(std::list<CardSnapshot>{CardSnapshot(*card2, CardSnapshot::ParamType::READING)}))
        .WillOnce(Return(std::list<CardSnapshot>{CardSnapshot(*card3, CardSnapshot::ParamType::READING)}));

    auto card = learner.getNextForRepeat(deck, CardSnapshot::ParamType::READING);
    EXPECT_EQ(card.getCard(), *card3);
}

TEST(SpacedRepetitionLearn_getNextForRepeat, AllReadyDiffer)
{
    std::shared_ptr<IModelManager> modelManager = std::shared_ptr<IModelManager>(new MockModelManager);
    MockModelManager& mockModelManager = *dynamic_cast<MockModelManager*>(modelManager.get());
    SpacedRepetitionLearn learner(modelManager);

    Deck deck;
    auto card1 = deck.addNewCard();
    auto card2 = deck.addNewCard();
    auto card3 = deck.addNewCard();

    *card1 = Card(L"card1", L"card1", L"card1");
    *card2 = Card(L"card2", L"card2", L"card2");
    *card3 = Card(L"card3", L"card3", L"card3");

    EXPECT_CALL(mockModelManager, getSnapshots)
        .Times(3)
        .WillOnce(Return(std::list<CardSnapshot>{CardSnapshot(*card1, CardSnapshot::ParamType::READING)}))
        .WillOnce(Return(std::list<CardSnapshot>{CardSnapshot(*card2, CardSnapshot::ParamType::READING)}))
        .WillOnce(Return(std::list<CardSnapshot>{CardSnapshot(*card3, CardSnapshot::ParamType::READING)}));

    EXPECT_ANY_THROW(learner.getNextForRepeat(deck, CardSnapshot::ParamType::TRANSLATION));
}
