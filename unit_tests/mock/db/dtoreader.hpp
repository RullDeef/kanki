#pragma once

#include <gmock/gmock.h>
#include "db/idbreader.hpp"

class MockDTOReader : public IDBReader
{
public:
    MOCK_METHOD(DBCard, readDBCard, (), (override));
    MOCK_METHOD(DBDeck, readDBDeck, (), (override));
    MOCK_METHOD(DBDeckCollection, readDBCollection, (), (override));
    MOCK_METHOD(DBSnapshot, readDBSnapshot, (), (override));
    MOCK_METHOD(DBSession, readDBSession, (), (override));
    MOCK_METHOD(size_t, readCount, (), (override));
};
