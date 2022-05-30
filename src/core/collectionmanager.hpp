#pragma once

#include "core/icollectionrepository.hpp"
#include "core/icollectionmanager.hpp"

class CollectionManager : public ICollectionManager
{
public:
    CollectionManager(ICollectionRepository *collectionRepository);

    virtual Collection getActiveCollection() override;

    virtual void saveCollection(const Collection &collection) override;

    virtual Collection getCollectionById(size_t id) override;

    virtual void deleteCollection(size_t id) override;

    virtual Deck getDeckById(size_t deckId) override;

    virtual Card getCardById(size_t cardId) override;

private:
    ICollectionRepository *collectionRepository;
};
