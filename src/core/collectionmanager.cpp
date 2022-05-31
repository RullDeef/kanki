#include <stdexcept>
#include "tools/logger.hpp"
#include "collectionmanager.hpp"

CollectionManager::CollectionManager(ICollectionRepository *collectionRepository)
    : collectionRepository(collectionRepository)
{
}

DeckCollection CollectionManager::getActiveCollection()
{
    auto collections = collectionRepository->getCollections();
    if (collections.empty())
    {
        ERROR_METHOD("collection is empty");
        throw std::runtime_error("collection is empty");
    }

    return collections.front();
}

void CollectionManager::saveCollection(const DeckCollection &collection)
{
    collectionRepository->saveCollection(collection);
}

DeckCollection CollectionManager::getCollectionById(UUID id)
{
    return collectionRepository->getCollectionById(id);
}

void CollectionManager::deleteCollection(UUID id)
{
    collectionRepository->removeCollection(id);
}

Deck CollectionManager::getDeckById(UUID deckId)
{
    for (auto collection : collectionRepository->getCollections())
        for (auto deck : collection)
            if (deck.getId() == deckId)
                return deck;

    throw std::runtime_error("invalid deck id");
}

Card CollectionManager::getCardById(UUID cardId)
{
    for (auto collection : collectionRepository->getCollections())
        for (auto deck : collection)
            for (auto card : deck)
                if (card.getId() == cardId)
                    return card;

    throw std::runtime_error("invalid card id");
}
