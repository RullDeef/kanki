#pragma once

#include <gmock/gmock.h>
#include "db/idtoreader.hpp"

class MockDTOReader : public IDTOReader
{
public:
    MOCK_METHOD(DBCard, readCardDTO, (), (override));
    MOCK_METHOD(DBDeck, readDeckDTO, (), (override));
    MOCK_METHOD(DBDeckCollection, readCollectionDTO, (), (override));
    MOCK_METHOD(DBSnapshot, readSnapshotDTO, (), (override));
    MOCK_METHOD(SessionDTO, readSessionDTO, (), (override));
    MOCK_METHOD(size_t, readCount, (), (override));
};
