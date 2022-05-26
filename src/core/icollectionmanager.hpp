#pragma once

#include "model/card.hpp"
#include "model/deck.hpp"
#include "model/collection.hpp"

class ICollectionManager
{
public:
    virtual ~ICollectionManager() = default;

    virtual Collection getActiveCollection() = 0;

    virtual void saveCollection(const Collection& collection) = 0;
    virtual Collection getCollectionById(size_t id) = 0;
    virtual void deleteCollection(size_t id) = 0;

    virtual Deck getDeckById(size_t deckId) = 0;
    virtual Card getCardById(size_t cardId) = 0;
};
