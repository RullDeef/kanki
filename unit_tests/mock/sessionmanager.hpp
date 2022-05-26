#pragma once

#include <gtest/gtest.h>
#include "core/isessionmanager.hpp"

class MockSessionManager : public ISessionManager
{
public:
    MOCK_METHOD(const Session&, getActiveSession, (), (override));
    MOCK_METHOD(void, addSnapshot, (const Snapshot& snapshot), (override));
    MOCK_METHOD(std::list<Snapshot>, getAllCardSnapshots, (const Card& card), (override));
};
