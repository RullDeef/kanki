#include <stdexcept>
#include "dto/dtocollectionbuilder.hpp"

DTOCollectionBuilder::DTOCollectionBuilder(const CollectionDTO &collectionDTO)
    : collectionDTO(collectionDTO)
{
}

void DTOCollectionBuilder::addDeckDTO(const DeckDTO &deckDTO)
{
    deckDTOs.push_back(deckDTO);
}

void DTOCollectionBuilder::addCardDTO(const CardDTO &cardDTO)
{
    cardDTOs.push_back(cardDTO);
}

Collection DTOCollectionBuilder::build()
{
    Collection collection(collectionDTO.id, collectionDTO.name);

    for (auto deckDTO : deckDTOs)
    {
        if (deckDTO.collectionId != collectionDTO.id)
            throw std::runtime_error("bad deckDTO.collectionId");

        collection.addDeck(buildDeck(deckDTO));
    }

    return collection;
}

Deck DTOCollectionBuilder::buildDeck(const DeckDTO &deckDTO)
{
    Deck deck(deckDTO.id, deckDTO.name);

    for (auto cardDTO : cardDTOs)
        if (cardDTO.deckId == deckDTO.id)
            deck.addCard(buildCard(cardDTO));

    return deck;
}

Card DTOCollectionBuilder::buildCard(const CardDTO &cardDTO)
{
    return Card(cardDTO.id,
                cardDTO.symbol,
                cardDTO.reading,
                cardDTO.description);
}
