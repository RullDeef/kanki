#pragma once

#include <list>
#include "model/deckcollection.hpp"

class ICollectionRepository
{
public:
    virtual ~ICollectionRepository() = default;

    virtual std::list<DeckCollection> getCollections() = 0;
    virtual DeckCollection getCollectionById(UUID id) = 0;
    virtual void removeCollection(UUID id) = 0;
    virtual void saveCollection(const DeckCollection& collection) = 0;
};
