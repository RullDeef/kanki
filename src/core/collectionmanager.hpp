#pragma once

#include <algorithm>
#include <list>
#include <stdexcept>
#include "model/collection.hpp"
#include "core/icollectionrepository.hpp"

class CollectionManager
{
public:
    CollectionManager(ICollectionRepository* collectionRepository)
        : collectionRepository(collectionRepository)
    {}

    Collection getActiveCollection() {
        auto collections = collectionRepository->getCollections();
        return collections.front();
    }

    void saveCollection(const Collection& collection) {
        collectionRepository->saveCollection(collection);
    }

    Collection getCollectionById(size_t id) {
        return collectionRepository->getCollectionById(id);
    }

    void deleteCollection(size_t id) {
        collectionRepository->removeCollection(id);
    }

    Deck getDeckById(size_t deckId) {
        for (auto collection : collectionRepository->getCollections())
            for (auto deck : collection)
                if (deck.getId() == deckId)
                    return deck;

        throw std::runtime_error("invalid deck id");
    }

    Card getCardById(size_t cardId) {
        for (auto collection : collectionRepository->getCollections())
            for (auto deck : collection)
                for (auto card : deck)
                    if (card.getId() == cardId)
                        return card;

        throw std::runtime_error("invalid card id");
    }

private:
    ICollectionRepository* collectionRepository;
};
