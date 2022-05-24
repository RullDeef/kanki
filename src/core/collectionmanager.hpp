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

private:
    ICollectionRepository* collectionRepository;
};
