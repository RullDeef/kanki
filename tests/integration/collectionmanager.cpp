#include <gtest/gtest.h>
#include "redis_integration_fixture.hpp"

TEST_F(RedisIntegrationFixture, CollectionManager_getActiveCollection)
{
    auto collection = collectionManager->getActiveCollection();

    auto expected = initialRepoState.front();
    ASSERT_EQ(collection, expected);
}

TEST_F(RedisIntegrationFixture, CollectionManager_saveCollection_empty)
{
    auto newCollection = DeckCollectionBuilder::random(0, 0).build();
    initialRepoState.push_back(newCollection);

    collectionManager->saveCollection(newCollection);

    auto actual = getCurrentRepoState();
    auto expected = initialRepoState;
    ASSERT_EQ(actual, expected);
}

TEST_F(RedisIntegrationFixture, CollectionManager_saveCollection_emptyDecks)
{
    auto newCollection = DeckCollectionBuilder::random(9, 0).build();
    initialRepoState.push_back(newCollection);

    collectionManager->saveCollection(newCollection);

    auto actual = getCurrentRepoState();
    auto expected = initialRepoState;
    ASSERT_EQ(actual, expected);
}

TEST_F(RedisIntegrationFixture, CollectionManager_saveCollection_notEmpty)
{
    auto newCollection = DeckCollectionBuilder::random(3, 6).build();
    initialRepoState.push_back(newCollection);

    collectionManager->saveCollection(newCollection);

    auto actual = getCurrentRepoState();
    auto expected = initialRepoState;
    ASSERT_EQ(actual, expected);
}
