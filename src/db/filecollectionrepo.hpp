#pragma once

#include "core/icollectionrepository.hpp"
#include "db/idtoreader.hpp"
#include "db/idtowriter.hpp"

class FileCollectionRepository : public ICollectionRepository
{
public:
    void load(IDTOReader &reader);
    void dump(IDTOWriter &writer);

    virtual std::list<Collection> getCollections() override;

    virtual Collection getCollectionById(size_t id) override;

    virtual void removeCollection(size_t id) override;
    virtual void saveCollection(const Collection &collection) override;

private:
    std::list<Collection> collections;
};
