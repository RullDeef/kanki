#pragma once

#include <gmock/gmock.h>
#include "core/icollectionmanager.hpp"

class MockCollectionManager : public ICollectionManager
{
public:
    MOCK_METHOD(Collection, getActiveCollection, (), (override));
    MOCK_METHOD(void, saveCollection, (const Collection &collection), (override));
    MOCK_METHOD(Collection, getCollectionById, (size_t id), (override));
    MOCK_METHOD(void, deleteCollection, (size_t id), (override));
    MOCK_METHOD(Deck, getDeckById, (size_t deckId), (override));
    MOCK_METHOD(Card, getCardById, (size_t cardId), (override));
};
