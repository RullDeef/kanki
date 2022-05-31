#pragma once

#include "model/deckcollection.hpp"
#include "db/model/card.hpp"
#include "db/model/deck.hpp"
#include "db/model/collection.hpp"

class DBCollectionBuilder
{
public:
    DBCollectionBuilder(const DBDeckCollection &collection);

    void addDeck(const DBDeck &deck);
    void addCard(const DBCard &card);

    DeckCollection build();

private:
    Deck buildDeck(const DBDeck &deck);
    Card buildCard(const DBCard &card);

    DBDeckCollection dbCollection;
    std::list<DBDeck> dbDecks;
    std::list<DBCard> dbCards;
};
