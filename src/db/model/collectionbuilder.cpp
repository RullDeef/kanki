#include <stdexcept>
#include "tools/logger.hpp"
#include "db/model/collectionbuilder.hpp"

DTOCollectionBuilder::DTOCollectionBuilder(const DBDeckCollection &collectionDTO)
    : collectionDTO(collectionDTO)
{
}

void DTOCollectionBuilder::addDeckDTO(const DBDeck &deckDTO)
{
    deckDTOs.push_back(deckDTO);
}

void DTOCollectionBuilder::addCardDTO(const DBCard &cardDTO)
{
    cardDTOs.push_back(cardDTO);
}

DeckCollection DTOCollectionBuilder::build()
{
    DeckCollection collection(collectionDTO.id, collectionDTO.name);

    for (auto deckDTO : deckDTOs)
    {
        if (deckDTO.collectionId != collectionDTO.id)
        {
            ERROR_METHOD("bad deckDTO.collectionId");
            throw std::runtime_error("bad deckDTO.collectionId");
        }

        collection.addDeck(buildDeck(deckDTO));
    }

    return collection;
}

Deck DTOCollectionBuilder::buildDeck(const DBDeck &deckDTO)
{
    Deck deck(deckDTO.id, deckDTO.name);

    for (auto cardDTO : cardDTOs)
        if (cardDTO.deckId == deckDTO.id)
            deck.addCard(buildCard(cardDTO));

    return deck;
}

Card DTOCollectionBuilder::buildCard(const DBCard &cardDTO)
{
    return Card(cardDTO.id,
                cardDTO.symbol,
                cardDTO.reading,
                cardDTO.description);
}
