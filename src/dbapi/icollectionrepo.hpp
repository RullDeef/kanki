#pragma once

#include <list>
#include <string>
#include "cardinfo.hpp"
#include "deckinfo.hpp"
#include "collectioninfo.hpp"

class ICollectionRepository
{
public:
    virtual ~ICollectionRepository() = default;

    virtual std::list<size_t> getCollectionIds() = 0;
    virtual std::list<size_t> getDeckIds(size_t collectionId) = 0;
    virtual std::list<size_t> getCardIds(size_t DeckId) = 0;

    virtual void setCollection(const CollectionInfo& collectionInfo) = 0;
    virtual void setDeck(const DeckInfo& deckInfo) = 0;
    virtual void setCard(const CardInfo& cardInfo) = 0;

    virtual CollectionInfo getCollection(size_t collectionId) = 0;
    virtual DeckInfo getDeck(size_t deckId) = 0;
    virtual CardInfo getCard(size_t cardId) = 0;

    virtual void deleteCollection(size_t collectionId) = 0;
    virtual void deleteDeck(size_t deckId) = 0;
    virtual void deleteCard(size_t cardId) = 0;
};
