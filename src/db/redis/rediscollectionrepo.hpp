#pragma once

#include <redis++.h>
#include "core/icollectionrepository.hpp"

class RedisCollectionRepository : public ICollectionRepository
{
public:
    RedisCollectionRepository(const std::string &url);

    virtual std::list<DeckCollection> getCollections() override;
    virtual DeckCollection getCollectionById(UUID id) override;
    virtual void removeCollection(UUID id) override;
    virtual void saveCollection(const DeckCollection &collection) override;

private:
    DeckCollection loadCollectionById(const std::string &id);

    void saveDeck(const Deck &deck);
    void saveCard(const Card &card);

    sw::redis::Redis connection;
};
