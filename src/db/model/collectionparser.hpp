#pragma once

#include <list>
#include "model/card.hpp"
#include "model/deck.hpp"
#include "model/deckcollection.hpp"
#include "db/model/card.hpp"
#include "db/model/deck.hpp"
#include "db/model/collection.hpp"

class DTOCollectionParser
{
public:
    DTOCollectionParser(const DeckCollection &collection);

    DBDeckCollection getCollectionDTO() const;
    DBDeck getDeckDTO(UUID id) const;
    DBCard getCardDTO(UUID id) const;

    std::list<UUID> getDeckIds() const;
    std::list<UUID> getCardIds(UUID deckId) const;

private:
    void decomposeDeck(const Deck &deck);
    void decomposeCard(uuids::uuid deckId, const Card &card);

    DBDeckCollection collectionDTO;
    std::list<DBDeck> deckDTOs;
    std::list<DBCard> cardDTOs;
};
