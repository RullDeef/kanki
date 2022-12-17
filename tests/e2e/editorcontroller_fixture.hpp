#pragma once

#include <gtest/gtest.h>
#include "db/redis/rediscollectionrepo.hpp"
#include "core/editorcontroller.hpp"
#include "core/collectionmanager.hpp"

constexpr auto REDIS_TEST_URL = "tcp://redis_test:6380";

class EditorControllerFixture : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        try
        {
            // setup redis database
            auto connection = sw::redis::Redis(REDIS_TEST_URL);
            setupDatabase(connection);

            collectionRepo = std::shared_ptr<ICollectionRepository>(
                new RedisCollectionRepository(REDIS_TEST_URL));

            editorController = std::make_unique<EditorController>(
                std::shared_ptr<ICollectionManager>(
                    new CollectionManager(
                        collectionRepo)));
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

    void setupDatabase(sw::redis::Redis &redis)
    {
    }

public:
    std::unique_ptr<EditorController> editorController;
    std::shared_ptr<ICollectionRepository> collectionRepo;
};
