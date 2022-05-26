#pragma once

#include <string>
#include "core/icollectionrepository.hpp"

class FileCollectionRepository : public ICollectionRepository
{
public:
    FileCollectionRepository(const std::string &filename);
    ~FileCollectionRepository();

    // loads data from disk
    void load();

    // writes data on disk
    void dump();

    virtual std::list<Collection> getCollections() override;

    virtual Collection getCollectionById(size_t id) override;

    virtual void removeCollection(size_t id) override;
    virtual void saveCollection(const Collection &collection) override;

private:
    std::string filename;
    std::list<Collection> collections;
};
