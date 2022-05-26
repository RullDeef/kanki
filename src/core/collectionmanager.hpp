#pragma once

#include <algorithm>
#include <list>
#include <stdexcept>
#include "core/icollectionrepository.hpp"
#include "core/icollectionmanager.hpp"

class CollectionManager : public ICollectionManager
{
public:
    CollectionManager(ICollectionRepository* collectionRepository)
        : collectionRepository(collectionRepository)
    {}

    virtual Collection getActiveCollection() override {
        auto collections = collectionRepository->getCollections();
        return collections.front();
    }

    virtual void saveCollection(const Collection& collection) override {
        collectionRepository->saveCollection(collection);
    }

    virtual Collection getCollectionById(size_t id) override {
        return collectionRepository->getCollectionById(id);
    }

    virtual void deleteCollection(size_t id) override {
        collectionRepository->removeCollection(id);
    }

    virtual Deck getDeckById(size_t deckId) override {
        for (auto collection : collectionRepository->getCollections())
            for (auto deck : collection)
                if (deck.getId() == deckId)
                    return deck;

        throw std::runtime_error("invalid deck id");
    }

    virtual Card getCardById(size_t cardId) override {
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
