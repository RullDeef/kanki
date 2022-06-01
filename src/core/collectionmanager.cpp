#include <stdexcept>
#include "tools/logger.hpp"
#include "collectionmanager.hpp"

CollectionManager::CollectionManager(std::shared_ptr<ICollectionRepository> collectionRepository)
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
    LOG_METHOD("collectionId=" + uuids::to_string(collection.getId()));

    collectionRepository->saveCollection(collection);
}

DeckCollection CollectionManager::getCollectionById(UUID id)
{
    LOG_METHOD("id=" + uuids::to_string(id));

    return collectionRepository->getCollectionById(id);
}

void CollectionManager::deleteCollection(UUID id)
{
    LOG_METHOD("id=" + uuids::to_string(id));

    collectionRepository->removeCollection(id);
}

Deck CollectionManager::getDeckById(UUID deckId)
{
    LOG_METHOD("deckId=" + uuids::to_string(deckId));

    for (auto collection : collectionRepository->getCollections())
        for (auto deck : collection)
            if (deck.getId() == deckId)
                return deck;

    throw std::runtime_error("invalid deck id");
}

Card CollectionManager::getCardById(UUID cardId)
{
    LOG_METHOD("cardId=" + uuids::to_string(cardId));

    for (auto collection : collectionRepository->getCollections())
        for (auto deck : collection)
            for (auto card : deck)
                if (card.getId() == cardId)
                    return card;

    throw std::runtime_error("invalid card id");
}
