#pragma once

#include "model/collection.hpp"
#include "dto/card.hpp"
#include "dto/deck.hpp"
#include "dto/collection.hpp"

class DTOCollectionBuilder
{
public:
    DTOCollectionBuilder(const CollectionDTO &collectionDTO);

    void addDeckDTO(const DeckDTO &deckDTO);
    void addCardDTO(const CardDTO &cardDTO);

    Collection build();

private:
    Deck buildDeck(const DeckDTO &deckDTO);
    Card buildCard(const CardDTO &cardDTO);

    CollectionDTO collectionDTO;
    std::list<DeckDTO> deckDTOs;
    std::list<CardDTO> cardDTOs;
};
