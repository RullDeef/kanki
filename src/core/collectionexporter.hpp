#pragma once

#include <memory>
#include <string>
#include "model/collection.hpp"
#include "dbapi/icollectionrepo.hpp"

class CollectionExporter
{
public:
    explicit CollectionExporter(std::shared_ptr<ICollectionRepository> collectionRepo);

    void exportCollection(const Collection& collection);
    Collection importCollection();

private:
    std::shared_ptr<ICollectionRepository> collectionRepo;
};
