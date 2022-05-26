#pragma once

#include <gtest/gtest.h>
#include "core/ilearnerview.hpp"

class MockLearnerView : public ILearnerView
{
public:
    MOCK_METHOD(void, showCard, (const Card &card), (override));
    MOCK_METHOD(void, askCard, (const Card &card), (override));

    MOCK_METHOD(void, noCardsForLearn, (), (override));
    MOCK_METHOD(void, noCardsForRepeat, (), (override));
};
