#pragma once

#include <gtest/gtest.h>
#include "core/ilearner.hpp"

class MockLearner : public ILearner
{
public:
    MOCK_METHOD(Card, getNextForLearn, (size_t deckId), (override));
    MOCK_METHOD(Card, getNextForRepeat, (size_t deckId), (override));
};
