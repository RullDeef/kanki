#include <fstream>
#include <locale>
#include <codecvt>
#include <algorithm>
#include "tools/logger.hpp"
#include "tools/convertor.hpp"
#include "filecollectionrepo.hpp"

static Collection loadCollection(const std::string& filename)
{
    std::wifstream file(filename);
    Collection collection;

    do
    {
        std::wstring deckName;
        std::getline(file, deckName);

        size_t deckSize;
        file >> deckSize >> std::ws;

        auto deck = collection.addNewDeck();
        deck->setName(Convert::toString(deckName));

        for (size_t i = 0; i < deckSize; i++)
        {
            std::wstring symbol, reading, description;
            std::getline(file, symbol);
            std::getline(file, reading);
            std::getline(file, description);

            deck->addCard(Card(symbol, reading, description));
        }
        file >> std::ws;
        //collection.addDeck(std::move(deck));
    }
    while (!file.eof());

    return std::move(collection);
}

FileCollectionRepository::FileCollectionRepository(const std::string& filename)
    : filename(filename), collection(0, "MainCollection")
{
    LOG_METHOD();

    auto coll = loadCollection(filename);
    size_t deckId = 0;
    size_t cardId = 0;

    for (const auto& deck : coll)
    {
        decks.emplace(deckId, DeckInfo(deckId, collection.id, deck->getName()));
        for (const auto& card : *deck)
        {
            cards.emplace(cardId, CardInfo(cardId, deckId,
                card->getSymbol(),
                card->getReading(),
                card->getDescription()));
            cardId++;
        }
        deckId++;
    }
}

FileCollectionRepository::~FileCollectionRepository()
{
    LOG_METHOD();

    std::wofstream file(filename);

    for (const auto& [deckId, deckInfo] : decks)
    {
        file << Convert::toWString(deckInfo.name) << std::endl;

        size_t deckSize = std::count_if(cards.begin(), cards.end(),
            [deckId](const std::pair<size_t, CardInfo>& c) {
                return c.second.deckId == deckId;
            });
        file << deckSize << std::endl;

        for (const auto& [cardId, cardInfo] : cards)
        {
            if (cardInfo.deckId == deckId)
            {
                file << cardInfo.symbol << std::endl;
                file << cardInfo.reading << std::endl;
                file << cardInfo.description << std::endl;
            }
        }
    }
}

std::list<size_t> FileCollectionRepository::getCollectionIds()
{
    ///TODO: implement (?)
    return {0};
}

std::list<size_t> FileCollectionRepository::getDeckIds(size_t collectionId)
{
    std::list<size_t> result;

    for (const auto& [id, info] : decks)
        if (info.collectionId == collectionId)
            result.push_back(id);

    return result;
}

std::list<size_t> FileCollectionRepository::getCardIds(size_t deckId)
{
    std::list<size_t> result;
    
    for (const auto& [id, info] : cards)
        if (info.deckId == deckId)
            result.push_back(id);

    return result;
}

CollectionInfo FileCollectionRepository::getCollection(size_t collectionId)
{
    return collection;
}

DeckInfo FileCollectionRepository::getDeck(size_t deckId)
{
    if (decks.count(deckId) == 0)
    {
        ERROR_METHOD("no such deckId: " + std::to_string(deckId));
        throw std::runtime_error("bad deckId");
    }
    
    return decks.at(deckId);
}

CardInfo FileCollectionRepository::getCard(size_t cardId)
{
    if (cards.count(cardId) == 0)
    {
        ERROR_METHOD("no such cardId: " + std::to_string(cardId));
        throw std::runtime_error("bad cardId");
    }
    
    return cards.at(cardId);
}

void FileCollectionRepository::deleteCollection(size_t collectionId)
{
    ///TODO: implement
    WARN_METHOD("not implemented");
}

void FileCollectionRepository::deleteDeck(size_t deckId)
{
    decks.erase(deckId);
}

void FileCollectionRepository::deleteCard(size_t cardId)
{
    cards.erase(cardId);
}

void FileCollectionRepository::setCollection(const CollectionInfo& collectionInfo)
{
    collection = collectionInfo;
}

void FileCollectionRepository::setDeck(const DeckInfo& deckInfo)
{
    if (decks.count(deckInfo.id) == 0)
        decks.emplace(deckInfo.id, deckInfo);
    else
        decks.at(deckInfo.id) = deckInfo;
}

void FileCollectionRepository::setCard(const CardInfo& cardInfo)
{
    if (cards.count(cardInfo.id) == 0)
        cards.emplace(cardInfo.id, cardInfo);
    else
        cards.at(cardInfo.id) = cardInfo;
}
