#pragma once

#include "tools/uuid.hpp"
#include "model/card.hpp"
#include "model/deck.hpp"
#include "model/deckcollection.hpp"

class ICollectionManager
{
public:
    virtual ~ICollectionManager() = default;

    virtual DeckCollection getActiveCollection() = 0;

    virtual void saveCollection(const DeckCollection& collection) = 0;
    virtual DeckCollection getCollectionById(UUID id) = 0;
    virtual void deleteCollection(UUID id) = 0;

    virtual Deck getDeckById(UUID deckId) = 0;
    virtual Card getCardById(UUID cardId) = 0;
};
