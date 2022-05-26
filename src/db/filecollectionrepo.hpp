#pragma once

#include "core/icollectionrepository.hpp"
#include "db/idtoiofactory.hpp"

class FileCollectionRepository : public ICollectionRepository
{
public:
    FileCollectionRepository(IDTOIOFactory* ioFactory);
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
    IDTOIOFactory* ioFactory;
    std::list<Collection> collections;
};
