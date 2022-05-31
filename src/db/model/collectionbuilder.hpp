#pragma once

#include "model/deckcollection.hpp"
#include "db/model/card.hpp"
#include "db/model/deck.hpp"
#include "db/model/collection.hpp"

class DTOCollectionBuilder
{
public:
    DTOCollectionBuilder(const DBDeckCollection &collectionDTO);

    void addDeckDTO(const DBDeck &deckDTO);
    void addCardDTO(const DBCard &cardDTO);

    DeckCollection build();

private:
    Deck buildDeck(const DBDeck &deckDTO);
    Card buildCard(const DBCard &cardDTO);

    DBDeckCollection collectionDTO;
    std::list<DBDeck> deckDTOs;
    std::list<DBCard> cardDTOs;
};
