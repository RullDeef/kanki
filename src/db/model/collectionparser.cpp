#include <stdexcept>
#include <algorithm>
#include "db/model/collectionparser.hpp"

DTOCollectionParser::DTOCollectionParser(const DeckCollection &collection)
{
    collectionDTO.id = collection.getId();
    collectionDTO.name = collection.getName();

    for (auto deck : collection)
        decomposeDeck(deck);
}

DBDeckCollection DTOCollectionParser::getCollectionDTO() const
{
    return collectionDTO;
}

DBDeck DTOCollectionParser::getDeckDTO(UUID id) const
{
    for (auto deckDTO : deckDTOs)
        if (deckDTO.id == id)
            return deckDTO;

    throw std::runtime_error("invalid deckDTO id");
}

DBCard DTOCollectionParser::getCardDTO(UUID id) const
{
    for (auto cardDTO : cardDTOs)
        if (cardDTO.id == id)
            return cardDTO;

    throw std::runtime_error("invalid cardDTO id");
}

std::list<UUID> DTOCollectionParser::getDeckIds() const
{
    std::list<UUID> ids(deckDTOs.size());

    std::transform(deckDTOs.begin(), deckDTOs.end(), ids.begin(),
                   [](const DBDeck &deckDTO)
                   { return deckDTO.id; });

    return ids;
}

std::list<UUID> DTOCollectionParser::getCardIds(UUID deckId) const
{
    std::list<UUID> ids;

    for (auto cardDTO : cardDTOs)
        if (cardDTO.deckId == deckId)
            ids.push_back(cardDTO.id);

    return ids;
}

void DTOCollectionParser::decomposeDeck(const Deck &deck)
{
    DBDeck deckDTO;
    deckDTO.id = deck.getId();
    deckDTO.collectionId = collectionDTO.id;
    deckDTO.name = deck.getName();

    for (auto card : deck)
        decomposeCard(deckDTO.id, card);

    deckDTOs.push_back(deckDTO);
}

void DTOCollectionParser::decomposeCard(UUID deckId, const Card &card)
{
    DBCard cardDTO;
    cardDTO.id = card.getId();
    cardDTO.deckId = deckId;

    cardDTO.symbol = card.getSymbol();
    cardDTO.reading = card.getReading();
    cardDTO.description = card.getDescription();

    cardDTOs.push_back(cardDTO);
}
