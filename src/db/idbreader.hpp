#pragma once

#include "db/model/card.hpp"
#include "db/model/deck.hpp"
#include "db/model/collection.hpp"
#include "db/model/snapshot.hpp"
#include "db/model/session.hpp"

class IDBReader
{
public:
    ~IDBReader() = default;

    virtual DBCard readDBCard() = 0;
    virtual DBDeck readDBDeck() = 0;
    virtual DBDeckCollection readDBCollection() = 0;

    virtual DBSnapshot readDBSnapshot() = 0;
    virtual DBSession readDBSession() = 0;

    virtual size_t readCount() = 0;
};
