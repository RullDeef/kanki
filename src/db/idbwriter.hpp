#pragma once

#include "db/model/card.hpp"
#include "db/model/deck.hpp"
#include "db/model/collection.hpp"
#include "db/model/snapshot.hpp"
#include "db/model/session.hpp"

class IDBWriter
{
public:
    ~IDBWriter() = default;

    virtual void writeDBCard(const DBCard &card) = 0;
    virtual void writeDBDeck(const DBDeck &deck) = 0;
    virtual void writeDBCollection(const DBDeckCollection &collection) = 0;

    virtual void writeDBSnapshot(const DBSnapshot &snapshot) = 0;
    virtual void writeDBSession(const DBSession &session) = 0;

    virtual void writeCount(size_t count) = 0;
};
