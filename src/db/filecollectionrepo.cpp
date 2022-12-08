#include <fstream>
#include "tools/logger.hpp"
#include "tools/idgenerator.hpp"
#include "db/model/collectionparser.hpp"
#include "db/model/collectionbuilder.hpp"
#include "db/filereader.hpp"
#include "db/filewriter.hpp"
#include "db/filecollectionrepo.hpp"

FileCollectionRepository::FileCollectionRepository(std::shared_ptr<IDTOIOFactory> ioFactory)
    : ioFactory(ioFactory)
{
    if (ioFactory)
        load();
}

FileCollectionRepository::~FileCollectionRepository()
{
    try
    {
        if (ioFactory)
            dump();
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD(e.what());
    }
}

void FileCollectionRepository::load()
{
    LOG_METHOD();

    try
    {
        auto reader = ioFactory->createReader();
        load(*reader);
    }
    catch(const std::exception& e)
    {
        ERROR_METHOD(e.what());
        // init default collection
        collections.push_back(DeckCollection::createDefault());
    }
}

void FileCollectionRepository::load(IDBReader &reader)
{
    LOG_METHOD();

    collections.clear();

    size_t collectionsCount = reader.readCount();
    for (size_t i = 0; i < collectionsCount; i++)
    {
        auto dbCollection = reader.readDBCollection();
        size_t decksCount = reader.readCount();
        DBCollectionBuilder collector(dbCollection);

        for (size_t j = 0; j < decksCount; j++)
        {
            auto deckDTO = reader.readDBDeck();
            size_t cardsCount = reader.readCount();
            collector.addDeck(deckDTO);

            for (size_t k = 0; k < cardsCount; k++)
            {
                auto cardDTO = reader.readDBCard();
                collector.addCard(cardDTO);
            }
        }

        collections.push_back(collector.build());
    }
}

void FileCollectionRepository::dump()
{
    try
    {
        if (!ioFactory) {
            throw std::runtime_error("ioFactory is null");
        }

        auto writer = ioFactory->createWriter();
        dump(*writer);
    }
    catch(const std::exception& e)
    {
        ERROR_METHOD(e.what());
        throw e;
    }
}

void FileCollectionRepository::dump(IDBWriter &writer)
{
    LOG_METHOD();

    writer.writeCount(collections.size());
    for (auto collection : collections)
    {
        DBCollectionParser parser(collection);
        writer.writeDBCollection(parser.getCollectionDTO());

        auto deckIds = parser.getDeckIds();
        writer.writeCount(deckIds.size());

        for (auto deckId : deckIds)
        {
            auto deckDTO = parser.getDeckDTO(deckId);
            writer.writeDBDeck(deckDTO);

            auto cardIds = parser.getCardIds(deckId);
            writer.writeCount(cardIds.size());

            for (auto cardId : cardIds)
            {
                auto cardDTO = parser.getCardDTO(cardId);
                writer.writeDBCard(cardDTO);
            }
        }
    }
}

std::list<DeckCollection> FileCollectionRepository::getCollections()
{
    return collections;
}

DeckCollection FileCollectionRepository::getCollectionById(UUID id)
{
    LOG_METHOD();

    auto iter = std::find_if(collections.begin(), collections.end(),
                             [id](const DeckCollection &collection)
                             { return collection.getId() == id; });

    if (iter == collections.end())
        throw std::runtime_error("bad collection id");
    return *iter;
}

void FileCollectionRepository::removeCollection(UUID id)
{
    LOG_METHOD();

    collections.erase(
        std::remove_if(collections.begin(), collections.end(),
                       [id](const DeckCollection &collection)
                       { return collection.getId() == id; }),
        collections.end());
}

void FileCollectionRepository::saveCollection(const DeckCollection &collection)
{
    LOG_METHOD();

    auto id = collection.getId();
    auto iter = std::find_if(collections.begin(), collections.end(),
                             [id](const DeckCollection &collection)
                             { return collection.getId() == id; });

    if (iter != collections.end())
        *iter = collection;
    else
        collections.push_back(collection);
}
