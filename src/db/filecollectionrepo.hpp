#pragma once

#include "core/icollectionrepository.hpp"
#include "db/idtoreader.hpp"
#include "db/idtowriter.hpp"

class FileCollectionRepository : public ICollectionRepository
{
public:
    void load(IDTOReader &reader);
    void dump(IDTOWriter &writer);

    virtual std::list<DeckCollection> getCollections() override;

    virtual DeckCollection getCollectionById(UUID id) override;

    virtual void removeCollection(UUID id) override;
    virtual void saveCollection(const DeckCollection &collection) override;

private:
    std::list<DeckCollection> collections;
};
