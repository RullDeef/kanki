#include <fstream>
#include "tools/logger.hpp"
#include "tools/idgenerator.hpp"
#include "dto/collectionparser.hpp"
#include "dto/collectionbuilder.hpp"
#include "db/filereader.hpp"
#include "db/filewriter.hpp"
#include "db/filecollectionrepo.hpp"

FileCollectionRepository::FileCollectionRepository(const std::string &filename)
    : filename(filename)
{
    try
    {
        load();
    }
    catch (const std::exception &e)
    {
        /// TODO: create default collection on failure
        ERROR_METHOD(e.what());
    }
}

FileCollectionRepository::~FileCollectionRepository()
{
    try
    {
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

    collections.clear();

    std::wifstream file(filename);
    FileReader reader(file);

    size_t collectionsCount = reader.readCount();
    for (size_t i = 0; i < collectionsCount; i++)
    {
        auto collectionDTO = reader.readCollectionDTO();
        size_t decksCount = reader.readCount();
        DTOCollectionBuilder collector(collectionDTO);

        for (size_t j = 0; j < decksCount; j++)
        {
            auto deckDTO = reader.readDeckDTO();
            size_t cardsCount = reader.readCount();
            collector.addDeckDTO(deckDTO);

            for (size_t k = 0; k < cardsCount; k++)
            {
                auto cardDTO = reader.readCardDTO();
                collector.addCardDTO(cardDTO);
            }
        }

        collections.push_back(collector.build());
    }
}

void FileCollectionRepository::dump()
{
    LOG_METHOD();

    std::wofstream file(filename);
    FileWriter writer(file);

    writer.writeCount(collections.size());
    for (auto collection : collections)
    {
        DTOCollectionParser parser(collection);
        writer.writeCollectionDTO(parser.getCollectionDTO());

        auto deckIds = parser.getDeckIds();
        writer.writeCount(deckIds.size());

        for (size_t deckId : deckIds)
        {
            auto deckDTO = parser.getDeckDTO(deckId);
            writer.writeDeckDTO(deckDTO);

            auto cardIds = parser.getCardIds(deckId);
            writer.writeCount(cardIds.size());

            for (size_t cardId : cardIds)
            {
                auto cardDTO = parser.getCardDTO(cardId);
                writer.writeCardDTO(cardDTO);
            }
        }
    }
}

std::list<Collection> FileCollectionRepository::getCollections()
{
    return collections;
}

Collection FileCollectionRepository::getCollectionById(size_t id)
{
    LOG_METHOD();

    auto iter = std::find_if(collections.begin(), collections.end(),
                             [id](const Collection &collection)
                             { return collection.getId() == id; });

    if (iter == collections.end())
        throw std::runtime_error("bad collection id");
    return *iter;
}

void FileCollectionRepository::removeCollection(size_t id)
{
    LOG_METHOD();

    collections.erase(
        std::remove_if(collections.begin(), collections.end(),
                       [id](const Collection &collection)
                       { return collection.getId() == id; }),
        collections.end());
}

void FileCollectionRepository::saveCollection(const Collection &collection)
{
    LOG_METHOD();

    size_t id = collection.getId();
    auto iter = std::find_if(collections.begin(), collections.end(),
                             [id](const Collection &collection)
                             { return collection.getId() == id; });

    if (iter != collections.end())
        *iter = collection;
    else
        collections.push_back(collection);
}
