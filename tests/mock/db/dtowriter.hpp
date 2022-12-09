#pragma once

#include <gmock/gmock.h>
#include "db/idbwriter.hpp"
#include "model/deckcollection.hpp"

class MockDTOWriter : public IDBWriter
{
public:
    void expectWrite(const std::initializer_list<DeckCollection> &collections);

    MOCK_METHOD(void, writeDBCard, (const DBCard &card), (override));
    MOCK_METHOD(void, writeDBDeck, (const DBDeck &deck), (override));
    MOCK_METHOD(void, writeDBCollection, (const DBDeckCollection &collection), (override));
    MOCK_METHOD(void, writeDBSnapshot, (const DBSnapshot &snapshot), (override));
    MOCK_METHOD(void, writeDBSession, (const DBSession &session), (override));
    MOCK_METHOD(void, writeCount, (size_t count), (override));
};
