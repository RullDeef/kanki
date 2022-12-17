#include <gtest/gtest.h>
#include "builders/deckbuilder.hpp"
#include "builders/cardbuilder.hpp"
#include "editorcontroller_fixture.hpp"

TEST_F(EditorControllerFixture, addCollection_emtpy)
{
    editorController->addCollection();
    editorController->saveActiveCollection();

    auto collections = collectionRepo->getCollections();
    ASSERT_EQ(collections.size(), 1);
}

TEST_F(EditorControllerFixture, addCollection_withDeck_withCard)
{
    editorController->addCollection();

    editorController->addDeck();
    editorController->setDeckName(L"deck #1");

    editorController->addCard();
    editorController->setCardSymbol(L"symmo");
    editorController->setCardReading(L"readdo");
    editorController->setCardDescription(L"descriptto");

    editorController->saveActiveCard();
    editorController->saveActiveDeck();
    editorController->saveActiveCollection();

    auto collections = collectionRepo->getCollections();
    ASSERT_EQ(collections.size(), 1);

    auto collection = collections.front();
    auto deck = *collection.begin();
    auto deckId = deck.getId();
    auto cardId = deck.begin()->getId();

    ASSERT_EQ(deck, DeckBuilder::random()
                        .withId(deckId)
                        .withName(L"deck #1")
                        .withCards({CardBuilder::random()
                                        .withId(cardId)
                                        .withSymbol(L"symmo")
                                        .withReading(L"readdo")
                                        .withDescription(L"descriptto").build()})
                        .build());
}
