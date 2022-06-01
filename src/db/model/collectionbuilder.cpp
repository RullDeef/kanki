#include <stdexcept>
#include "tools/logger.hpp"
#include "db/model/collectionbuilder.hpp"

DBCollectionBuilder::DBCollectionBuilder(const DBDeckCollection &collection)
    : dbCollection(collection)
{
}

void DBCollectionBuilder::addDeck(const DBDeck &dbDeck)
{
    dbDecks.push_back(dbDeck);
}

void DBCollectionBuilder::addCard(const DBCard &dbCard)
{
    dbCards.push_back(dbCard);
}

DeckCollection DBCollectionBuilder::build()
{
    DeckCollection collection(dbCollection.id, dbCollection.name);

    for (auto dbDeck : dbDecks)
    {
        if (dbDeck.collectionId != dbCollection.id)
        {
            ERROR_METHOD("bad dbDeck.collectionId");
            throw std::runtime_error("bad dbDeck.collectionId");
        }

        collection.addDeck(buildDeck(dbDeck));
    }

    return collection;
}

Deck DBCollectionBuilder::buildDeck(const DBDeck &dbDeck)
{
    Deck deck(dbDeck.id, dbDeck.name);

    for (auto dbCard : dbCards)
        if (dbCard.deckId == dbDeck.id)
            deck.addCard(buildCard(dbCard));

    return deck;
}

Card DBCollectionBuilder::buildCard(const DBCard &dbCard)
{
    return Card(dbCard.id,
                dbCard.symbol,
                dbCard.reading,
                dbCard.description);
}
