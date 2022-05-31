#pragma once

#include <gmock/gmock.h>
#include "core/icollectionmanager.hpp"

class MockCollectionManager : public ICollectionManager
{
public:
    MOCK_METHOD(DeckCollection, getActiveCollection, (), (override));
    MOCK_METHOD(void, saveCollection, (const DeckCollection &collection), (override));
    MOCK_METHOD(DeckCollection, getCollectionById, (UUID id), (override));
    MOCK_METHOD(void, deleteCollection, (UUID id), (override));
    MOCK_METHOD(Deck, getDeckById, (UUID deckId), (override));
    MOCK_METHOD(Card, getCardById, (UUID cardId), (override));
};
