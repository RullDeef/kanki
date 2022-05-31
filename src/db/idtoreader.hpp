#pragma once

#include "db/model/card.hpp"
#include "db/model/deck.hpp"
#include "db/model/collection.hpp"
#include "db/model/snapshot.hpp"
#include "db/model/session.hpp"

class IDTOReader
{
public:
    ~IDTOReader() = default;

    virtual DBCard readCardDTO() = 0;
    virtual DBDeck readDeckDTO() = 0;
    virtual DBDeckCollection readCollectionDTO() = 0;

    virtual DBSnapshot readSnapshotDTO() = 0;
    virtual SessionDTO readSessionDTO() = 0;

    virtual size_t readCount() = 0;
};
