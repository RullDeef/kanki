#pragma once

#ifndef USE_FEATURE_DB_REDIS
#error Integration tests must be built with USE_FEATURE_DB_REDIS enabled
#endif

#include <gtest/gtest.h>
#include <redis++.h>
#include "db/redis/rediscollectionrepo.hpp"
#include "builders/collectionbuilder.hpp"
#include "core/collectionmanager.hpp"

constexpr auto REDIS_TEST_URL = "tcp://redis_test:6380";

class RedisIntegrationFixture : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        initialRepoState = {
            DeckCollectionBuilder::random(7, 20).build(),
            DeckCollectionBuilder::random(1, 3).build(),
            DeckCollectionBuilder::random(6, 10).build(),
            DeckCollectionBuilder::random(3, 6).build(),
        };

        // setup redis database
        auto repo = std::shared_ptr<ICollectionRepository>(
            new RedisCollectionRepository(REDIS_TEST_URL));

        for (const auto &collection : initialRepoState)
            repo->saveCollection(collection);

        collectionManager = std::make_unique<CollectionManager>(repo);
    }

    virtual void TearDown() override
    {
        // drop collection manager to prevent database corruption
        collectionManager = nullptr;

        // clear all data from testing database
        auto connection = sw::redis::Redis(REDIS_TEST_URL);
        connection.flushdb();
    }

public:
    std::list<DeckCollection> initialRepoState;
    std::unique_ptr<CollectionManager> collectionManager;

    std::list<DeckCollection> getCurrentRepoState()
    {
        auto repo = RedisCollectionRepository(REDIS_TEST_URL);
        return repo.getCollections();
    }
};
