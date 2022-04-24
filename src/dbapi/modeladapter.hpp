#pragma once

#include <memory>
#include "model/card.hpp"
#include "model/deck.hpp"
#include "model/collection.hpp"
#include "model/cardsnapshot.hpp"
#include "model/session.hpp"
#include "cardinfo.hpp"
#include "deckinfo.hpp"
#include "collectioninfo.hpp"
#include "icollectionrepo.hpp"

class ModelInfoAdapter
{
public:
    explicit ModelInfoAdapter(std::shared_ptr<ICollectionRepository> repository);

    Collection extractCollection(size_t collectionId);
    Collection extractCollection(const CollectionInfo& collectionInfo);

    Deck extractDeck(size_t deckId);
    Deck extractDeck(const std::string& deckName);
    Deck extractDeck(const DeckInfo& deckInfo);

    Card extractCard(size_t cardId);
    Card extractCard(const CardInfo& cardInfo);

private:
    std::shared_ptr<ICollectionRepository> repository;
};
