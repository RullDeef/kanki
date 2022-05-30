#include <stdexcept>
#include <algorithm>
#include "dto/collectionparser.hpp"

DTOCollectionParser::DTOCollectionParser(const Collection &collection)
{
    collectionDTO.id = collection.getId();
    collectionDTO.name = collection.getName();

    for (auto deck : collection)
        decomposeDeck(deck);
}

CollectionDTO DTOCollectionParser::getCollectionDTO() const
{
    return collectionDTO;
}

DeckDTO DTOCollectionParser::getDeckDTO(size_t id) const
{
    for (auto deckDTO : deckDTOs)
        if (deckDTO.id == id)
            return deckDTO;

    throw std::runtime_error("invalid deckDTO id");
}

CardDTO DTOCollectionParser::getCardDTO(size_t id) const
{
    for (auto cardDTO : cardDTOs)
        if (cardDTO.id == id)
            return cardDTO;

    throw std::runtime_error("invalid cardDTO id");
}

std::list<size_t> DTOCollectionParser::getDeckIds() const
{
    std::list<size_t> ids(deckDTOs.size());

    std::transform(deckDTOs.begin(), deckDTOs.end(), ids.begin(),
                   [](const DeckDTO &deckDTO)
                   { return deckDTO.id; });

    return ids;
}

std::list<size_t> DTOCollectionParser::getCardIds(size_t deckId) const
{
    std::list<size_t> ids;

    for (auto cardDTO : cardDTOs)
        if (cardDTO.deckId == deckId)
            ids.push_back(cardDTO.id);

    return ids;
}

void DTOCollectionParser::decomposeDeck(const Deck &deck)
{
    DeckDTO deckDTO;
    deckDTO.id = deck.getId();
    deckDTO.collectionId = collectionDTO.id;
    deckDTO.name = deck.getName();

    for (auto card : deck)
        decomposeCard(deckDTO.id, card);

    deckDTOs.push_back(deckDTO);
}

void DTOCollectionParser::decomposeCard(size_t deckId, const Card &card)
{
    CardDTO cardDTO;
    cardDTO.id = card.getId();
    cardDTO.deckId = deckId;

    cardDTO.symbol = card.getSymbol();
    cardDTO.reading = card.getReading();
    cardDTO.description = card.getDescription();

    cardDTOs.push_back(cardDTO);
}
