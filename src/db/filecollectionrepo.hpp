#pragma once

#include <memory>
#include "core/icollectionrepository.hpp"
#include "db/idbiofactory.hpp"

class FileCollectionRepository : public ICollectionRepository
{
public:
    FileCollectionRepository(std::shared_ptr<IDTOIOFactory> ioFactory = nullptr);
    ~FileCollectionRepository();

    void load();
    void load(IDBReader &reader);

    void dump();
    void dump(IDBWriter &writer);

    virtual std::list<DeckCollection> getCollections() override;

    virtual DeckCollection getCollectionById(UUID id) override;

    virtual void removeCollection(UUID id) override;
    virtual void saveCollection(const DeckCollection &collection) override;

private:
    std::list<DeckCollection> collections;
    std::shared_ptr<IDTOIOFactory> ioFactory;
};
