#pragma once

#include <gtest/gtest.h>
#include <redis++.h>
#include "tools/uuid.hpp"
#include "tools/convertor.hpp"
#include "model/deckcollection.hpp"
#include "builders/collectionbuilder.hpp"

constexpr auto REDIS_TEST_URL = "tcp://localhost:6380";

class RedisBlankFixture : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        try
        {
            // setup redis database
            auto connection = sw::redis::Redis(REDIS_TEST_URL);
            setupDatabase(connection);
        }
        catch (const sw::redis::Error &e)
        {
            GTEST_SKIP() << "could not connect to test redis instance. Skipping tests...";
        }
    }

    virtual void TearDown() override
    {
        try
        {
            // clear all data from testing database
            auto connection = sw::redis::Redis(REDIS_TEST_URL);
            connection.flushdb();
        }
        catch (const std::exception &e)
        {
            GTEST_FAIL() << "got exception on fixture cleanup: " << e.what();
        }
    }

    virtual void setupDatabase(sw::redis::Redis &connection) {}
};

class RedisSingleEmptyCollectionFixture : public RedisBlankFixture
{
protected:
    RedisSingleEmptyCollectionFixture()
        : targetCollection(DeckCollectionBuilder::random(0, 0).build())
    {
    }

    virtual void setupDatabase(sw::redis::Redis &connection)
    {
        auto id = uuids::to_string(targetCollection.getId());

        connection.rpush("collection_ids", id);
        connection.hset("collection:" + id, "name", Convert().toString(targetCollection.getName()));
    }

public:
    DeckCollection targetCollection;
};
