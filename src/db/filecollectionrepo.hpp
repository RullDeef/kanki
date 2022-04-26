#pragma once

#include <map>
#include "model/collection.hpp"
#include "dbapi/icollectionrepo.hpp"

class FileCollectionRepository : public ICollectionRepository
{
public:
    explicit FileCollectionRepository(const std::string& filename);
    ~FileCollectionRepository();

    virtual std::list<size_t> getCollectionIds() override;
    virtual std::list<size_t> getDeckIds(size_t collectionId) override;
    virtual std::list<size_t> getCardIds(size_t deckId) override;

    virtual CollectionInfo getCollection(size_t id) override;
    virtual DeckInfo getDeck(size_t deckId) override;
    virtual CardInfo getCard(size_t cardId) override;

    virtual void setCollection(const CollectionInfo& collectionInfo) override;
    virtual void setDeck(const DeckInfo& deckInfo) override;
    virtual void setCard(const CardInfo& cardInfo) override;

    virtual void deleteCollection(size_t collectionId) override;
    virtual void deleteDeck(size_t deckId) override;
    virtual void deleteCard(size_t cardId) override;

private:
    void saveCollection();

    std::string filename;

    CollectionInfo collection;
    std::map<size_t, DeckInfo> decks;
    std::map<size_t, CardInfo> cards;
};
