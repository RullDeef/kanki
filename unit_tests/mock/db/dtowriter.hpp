#pragma once

#include <gmock/gmock.h>
#include "db/idtowriter.hpp"

class MockDTOWriter : public IDTOWriter
{
public:
    MOCK_METHOD(void, writeCardDTO, (const CardDTO &card), (override));
    MOCK_METHOD(void, writeDeckDTO, (const DeckDTO &deck), (override));
    MOCK_METHOD(void, writeCollectionDTO, (const CollectionDTO &collection), (override));
    MOCK_METHOD(void, writeSnapshotDTO, (const SnapshotDTO &snapshot), (override));
    MOCK_METHOD(void, writeSessionDTO, (const SessionDTO &session), (override));
    MOCK_METHOD(void, writeCount, (size_t count), (override));
};
