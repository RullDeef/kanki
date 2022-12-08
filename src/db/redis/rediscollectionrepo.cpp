#include "tools/logger.hpp"
#include "tools/convertor.hpp"
#include "db/redis/rediscollectionrepo.hpp"

RedisCollectionRepository::RedisCollectionRepository(const std::string &url)
try : connection(url)
{
    LOG_METHOD("url=" + url);
}
catch (const std::exception &e)
{
    ERROR_METHOD(e.what());
    throw e;
}

std::list<DeckCollection> RedisCollectionRepository::getCollections()
{
    LOG_METHOD();

    try
    {
        std::list<DeckCollection> collections;
        std::vector<std::string> ids;

        connection.lrange("collection_ids", 0, -1, std::back_inserter(ids));

        for (const auto &id : ids)
            collections.push_back(loadCollectionById(id));

        return collections;
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD(e.what());
        throw e;
    }
}

DeckCollection RedisCollectionRepository::getCollectionById(UUID id)
{
    LOG_METHOD(uuids::to_string(id));

    try
    {
        return loadCollectionById(uuids::to_string(id));
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD(e.what());
        throw e;
    }
}

void RedisCollectionRepository::removeCollection(UUID id)
{
    LOG_METHOD("id=" + uuids::to_string(id));

    try
    {
        /// TODO: cleanup db memory
        auto key = std::string("collection:") + uuids::to_string(id);
        auto count = connection.lrem("collection_ids", 0, uuids::to_string(id));

        if (count == 0)
            throw std::runtime_error("collection with id=" + uuids::to_string(id) + " not found");
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD(e.what());
        throw e;
    }
}

void RedisCollectionRepository::saveCollection(const DeckCollection &collection)
{
    LOG_METHOD("id=" + uuids::to_string(collection.getId()));

    try
    {
        auto uuid = uuids::to_string(collection.getId());

        // if key does not exist - add it
        std::vector<std::string> ids;
        connection.lrange("collection_ids", 0, -1, std::back_inserter(ids));
        auto pos = std::find(ids.begin(), ids.end(), uuid);
        if (pos == ids.end())
            connection.rpush("collection_ids", uuid);
        
        connection.hset("collection:" + uuid, "name", Convert().toString(collection.getName()));

        // rewrite deck ids
        auto key_deck_ids = std::string("collection:") + uuid + ":deck_ids";
        connection.del(key_deck_ids);

        // save decks
        for (const auto &deck : collection)
        {
            saveDeck(deck);
            connection.rpush(key_deck_ids, uuids::to_string(deck.getId()));
        }
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD(e.what());
        throw e;
    }
}

DeckCollection RedisCollectionRepository::loadCollectionById(const std::string &id)
{
    auto key = std::string("collection:") + id;

    if (!connection.hexists(key, "name"))
        throw std::runtime_error("collection with id=" + id + "has no field 'name'");
    auto name = Convert().toWString(*connection.hget(key, "name"));

    DeckCollection collection(*uuids::uuid::from_string(id), name);
    std::vector<std::string> deck_ids;

    connection.lrange(key + ":deck_ids", 0, -1, std::back_inserter(deck_ids));

    for (const auto &id : deck_ids)
    {
        auto key = std::string("deck:") + id;
        auto name = Convert().toWString(*connection.hget(key, "name"));

        Deck deck(*uuids::uuid::from_string(id), name);
        std::vector<std::string> card_ids;
        connection.lrange(key + ":card_ids", 0, -1, std::back_inserter(card_ids));

        for (const auto &id : card_ids)
        {
            auto key = std::string("card:") + id;
            auto symbol = Convert().toWString(*connection.hget(key, "symbol"));
            auto reading = Convert().toWString(*connection.hget(key, "reading"));
            auto description = Convert().toWString(*connection.hget(key, "description"));

            deck.addCard(Card(*uuids::uuid::from_string(id), symbol, reading, description));
        }

        collection.addDeck(deck);
    }

    return collection;
}

void RedisCollectionRepository::saveDeck(const Deck &deck)
{
    auto uuid = uuids::to_string(deck.getId());

    /// TODO: fix bug - possible garbage growth - if decks and
    // cards will not be free'd completely before write
    // rewrite card ids
    auto key_card_ids = std::string("deck:") + uuid + ":card_ids";
    connection.del(key_card_ids);
    connection.hset(std::string("deck:") + uuid, "name", Convert().toString(deck.getName()));

    // save cards
    for (const auto &card : deck)
    {
        saveCard(card);
        connection.rpush(key_card_ids, uuids::to_string(card.getId()));
    }
}

void RedisCollectionRepository::saveCard(const Card &card)
{
    auto uuid = uuids::to_string(card.getId());
    auto key_card = std::string("card:") + uuid;

    connection.hset(key_card, "symbol", Convert().toString(card.getSymbol()));
    connection.hset(key_card, "reading", Convert().toString(card.getReading()));
    connection.hset(key_card, "description", Convert().toString(card.getDescription()));
}
