#pragma once

#include <gmock/gmock.h>
#include "db/idbwriter.hpp"

class MockDTOWriter : public IDBWriter
{
public:
    MOCK_METHOD(void, writeDBCard, (const DBCard &card), (override));
    MOCK_METHOD(void, writeDBDeck, (const DBDeck &deck), (override));
    MOCK_METHOD(void, writeDBCollection, (const DBDeckCollection &collection), (override));
    MOCK_METHOD(void, writeDBSnapshot, (const DBSnapshot &snapshot), (override));
    MOCK_METHOD(void, writeDBSession, (const DBSession &session), (override));
    MOCK_METHOD(void, writeCount, (size_t count), (override));
};
