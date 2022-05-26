#pragma once

#include <list>
#include "model/card.hpp"
#include "model/deck.hpp"
#include "model/collection.hpp"
#include "dto/card.hpp"
#include "dto/deck.hpp"
#include "dto/collection.hpp"

class DTOParser
{
public:
    DTOParser(const Collection &collection);

    CollectionDTO getCollectionDTO() const;
    DeckDTO getDeckDTO(size_t id) const;
    CardDTO getCardDTO(size_t id) const;

    std::list<size_t> getDeckIds() const;
    std::list<size_t> getCardIds(size_t deckId) const;

private:
    void decomposeDeck(const Deck &deck);
    void decomposeCard(size_t deckId, const Card &card);

    CollectionDTO collectionDTO;
    std::list<DeckDTO> deckDTOs;
    std::list<CardDTO> cardDTOs;
};
