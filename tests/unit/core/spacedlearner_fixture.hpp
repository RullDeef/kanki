#pragma once

#include <gtest/gtest.h>
#include "mock/core/collectionmanager.hpp"
#include "mock/core/sessionmanager.hpp"
#include "core/spacedlearner.hpp"

class SpacedLearnerFixture : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        collectionManager = new MockCollectionManager();
        sessionManager = new MockSessionManager();

        i_collectionManager = std::shared_ptr<ICollectionManager>(collectionManager);
        i_sessionManager = std::shared_ptr<ISessionManager>(sessionManager);

        learner.useCollectionManager(i_collectionManager);
        learner.useSessionManager(i_sessionManager);
    }

public:
    SpacedLearner learner;
    MockCollectionManager *collectionManager;
    MockSessionManager *sessionManager;

private:
    std::shared_ptr<ICollectionManager> i_collectionManager;
    std::shared_ptr<ISessionManager> i_sessionManager;
};
