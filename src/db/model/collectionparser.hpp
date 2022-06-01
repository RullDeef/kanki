#pragma once

#include <list>
#include "model/card.hpp"
#include "model/deck.hpp"
#include "model/deckcollection.hpp"
#include "db/model/card.hpp"
#include "db/model/deck.hpp"
#include "db/model/collection.hpp"

class DBCollectionParser
{
public:
    DBCollectionParser(const DeckCollection &collection);

    DBDeckCollection getCollectionDTO() const;
    DBDeck getDeckDTO(UUID id) const;
    DBCard getCardDTO(UUID id) const;

    std::list<UUID> getDeckIds() const;
    std::list<UUID> getCardIds(UUID deckId) const;

private:
    void decomposeDeck(const Deck &deck);
    void decomposeCard(uuids::uuid deckId, const Card &card);

    DBDeckCollection dbCollection;
    std::list<DBDeck> dbDecks;
    std::list<DBCard> dbCards;
};
