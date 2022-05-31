#pragma once

#include "core/icollectionrepository.hpp"
#include "core/icollectionmanager.hpp"

class CollectionManager : public ICollectionManager
{
public:
    CollectionManager(ICollectionRepository *collectionRepository);

    virtual DeckCollection getActiveCollection() override;

    virtual void saveCollection(const DeckCollection &collection) override;

    virtual DeckCollection getCollectionById(UUID id) override;

    virtual void deleteCollection(UUID id) override;

    virtual Deck getDeckById(UUID deckId) override;

    virtual Card getCardById(UUID cardId) override;

private:
    ICollectionRepository *collectionRepository;
};
