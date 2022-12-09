#pragma once

#include <gtest/gtest.h>
#include "core/iestimator.hpp"

class MockEstimator : public IEstimator
{
public:
    MOCK_METHOD(void, markEasy, (Snapshot& snapshot), (override));
    MOCK_METHOD(void, markGood, (Snapshot& snapshot), (override));
    MOCK_METHOD(void, markAgain, (Snapshot& snapshot), (override));
};
