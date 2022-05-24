#pragma once

#include <list>
#include "model/collection.hpp"

class ICollectionRepository
{
public:
    virtual ~ICollectionRepository() = default;

    virtual std::list<Collection> getCollections() = 0;
    virtual Collection getCollectionById(size_t id) = 0;
    virtual void removeCollection(size_t id) = 0;
    virtual void saveCollection(const Collection& collection) = 0;
};
