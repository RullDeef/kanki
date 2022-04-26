#pragma once

#include <gmock/gmock.h>
#include "core/imodelmanager.hpp"

class MockModelManager : public IModelManager
{
public:
    MOCK_METHOD(std::shared_ptr<Collection>, getCollection, (), (override));
    MOCK_METHOD(std::shared_ptr<Session>, getActiveSession, (), (override));
    MOCK_METHOD(std::list<CardSnapshot>, getSnapshots, (const Card& card), (override));
    MOCK_METHOD(void, setCollection, (const Collection& newCollection), (override));
};
