#ifdef USE_FEATURE_REDIS
#include <gtest/gtest.h>
#include "db/redis/rediscollectionrepo.hpp"
#include "redis_fixture.hpp"
#include "builders/builder_base.hpp"
#include "builders/deckbuilder.hpp"
#include "builders/collectionbuilder.hpp"

TEST_F(RedisBlankFixture, RedisCollectionRepo_getCollections_noCollection)
{
    RedisCollectionRepository repo(REDIS_TEST_URL);

    auto collections = repo.getCollections();

    ASSERT_TRUE(collections.empty());
}

TEST_F(RedisSingleEmptyCollectionFixture, RedisCollectionRepo_getCollections_singleEmpty)
{
    RedisCollectionRepository repo(REDIS_TEST_URL);

    auto collections = repo.getCollections();

    ASSERT_EQ(collections, std::list{targetCollection});
}

TEST_F(RedisSingleEmptyCollectionFixture, RedisCollectionRepo_getCollectionById_success)
{
    RedisCollectionRepository repo(REDIS_TEST_URL);

    auto collection = repo.getCollectionById(targetCollection.getId());

    ASSERT_EQ(collection, targetCollection);
}

TEST_F(RedisSingleEmptyCollectionFixture, RedisCollectionRepo_getCollectionById_fail)
{
    RedisCollectionRepository repo(REDIS_TEST_URL);

    ASSERT_ANY_THROW(repo.getCollectionById(gen_random_uuid()));
}

TEST_F(RedisSingleEmptyCollectionFixture, RedisCollectionRepo_removeCollection_success)
{
    RedisCollectionRepository repo(REDIS_TEST_URL);

    repo.removeCollection(targetCollection.getId());

    auto collections = repo.getCollections();
    ASSERT_TRUE(collections.empty());
}

TEST_F(RedisSingleEmptyCollectionFixture, RedisCollectionRepo_removeCollection_fail)
{
    RedisCollectionRepository repo(REDIS_TEST_URL);

    ASSERT_ANY_THROW(repo.removeCollection(gen_random_uuid()));

    auto collections = repo.getCollections();
    ASSERT_EQ(collections, std::list{targetCollection});
}

TEST_F(RedisSingleEmptyCollectionFixture, RedisCollectionRepo_saveCollection_addsNew)
{
    RedisCollectionRepository repo(REDIS_TEST_URL);

    auto testCollection = DeckCollectionBuilder::random(0, 0)
                              .withDecks({DeckBuilder::random(1).build(),
                                          DeckBuilder::random(3).build(),
                                          DeckBuilder::random(0).build()})
                              .build();

    repo.saveCollection(testCollection);

    auto res = repo.getCollectionById(testCollection.getId());
    ASSERT_EQ(res, testCollection);
}

#endif
