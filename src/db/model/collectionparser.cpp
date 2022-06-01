#include <stdexcept>
#include <algorithm>
#include "db/model/collectionparser.hpp"

DBCollectionParser::DBCollectionParser(const DeckCollection &collection)
{
    dbCollection.id = collection.getId();
    dbCollection.name = collection.getName();

    for (auto deck : collection)
        decomposeDeck(deck);
}

DBDeckCollection DBCollectionParser::getCollectionDTO() const
{
    return dbCollection;
}

DBDeck DBCollectionParser::getDeckDTO(UUID id) const
{
    for (auto dbDeck : dbDecks)
        if (dbDeck.id == id)
            return dbDeck;

    throw std::runtime_error("invalid dbDeck id");
}

DBCard DBCollectionParser::getCardDTO(UUID id) const
{
    for (auto dbCard : dbCards)
        if (dbCard.id == id)
            return dbCard;

    throw std::runtime_error("invalid dbCard id");
}

std::list<UUID> DBCollectionParser::getDeckIds() const
{
    std::list<UUID> ids(dbDecks.size());

    std::transform(dbDecks.begin(), dbDecks.end(), ids.begin(),
                   [](const DBDeck &dbDeck)
                   { return dbDeck.id; });

    return ids;
}

std::list<UUID> DBCollectionParser::getCardIds(UUID deckId) const
{
    std::list<UUID> ids;

    for (auto dbCard : dbCards)
        if (dbCard.deckId == deckId)
            ids.push_back(dbCard.id);

    return ids;
}

void DBCollectionParser::decomposeDeck(const Deck &deck)
{
    DBDeck dbDeck;
    dbDeck.id = deck.getId();
    dbDeck.collectionId = dbCollection.id;
    dbDeck.name = deck.getName();

    for (auto card : deck)
        decomposeCard(dbDeck.id, card);

    dbDecks.push_back(dbDeck);
}

void DBCollectionParser::decomposeCard(UUID deckId, const Card &card)
{
    DBCard dbCard;
    dbCard.id = card.getId();
    dbCard.deckId = deckId;

    dbCard.symbol = card.getSymbol();
    dbCard.reading = card.getReading();
    dbCard.description = card.getDescription();

    dbCards.push_back(dbCard);
}
