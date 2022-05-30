#pragma once

#include <gmock/gmock.h>
#include "db/idtoreader.hpp"

class MockDTOReader : public IDTOReader
{
public:
    MOCK_METHOD(CardDTO, readCardDTO, (), (override));
    MOCK_METHOD(DeckDTO, readDeckDTO, (), (override));
    MOCK_METHOD(CollectionDTO, readCollectionDTO, (), (override));
    MOCK_METHOD(SnapshotDTO, readSnapshotDTO, (), (override));
    MOCK_METHOD(SessionDTO, readSessionDTO, (), (override));
    MOCK_METHOD(size_t, readCount, (), (override));
};
