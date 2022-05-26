#include <stdexcept>
#include "collectionmanager.hpp"

CollectionManager::CollectionManager(ICollectionRepository *collectionRepository)
    : collectionRepository(collectionRepository)
{
}

Collection CollectionManager::getActiveCollection()
{
    auto collections = collectionRepository->getCollections();
    return collections.front();
}

void CollectionManager::saveCollection(const Collection &collection)
{
    collectionRepository->saveCollection(collection);
}

Collection CollectionManager::getCollectionById(size_t id)
{
    return collectionRepository->getCollectionById(id);
}

void CollectionManager::deleteCollection(size_t id)
{
    collectionRepository->removeCollection(id);
}

Deck CollectionManager::getDeckById(size_t deckId)
{
    for (auto collection : collectionRepository->getCollections())
        for (auto deck : collection)
            if (deck.getId() == deckId)
                return deck;

    throw std::runtime_error("invalid deck id");
}

Card CollectionManager::getCardById(size_t cardId)
{
    for (auto collection : collectionRepository->getCollections())
        for (auto deck : collection)
            for (auto card : deck)
                if (card.getId() == cardId)
                    return card;

    throw std::runtime_error("invalid card id");
}
