#pragma once

#include "dto/card.hpp"
#include "dto/deck.hpp"
#include "dto/collection.hpp"
#include "dto/snapshot.hpp"
#include "dto/session.hpp"

class IDTOReader
{
public:
    ~IDTOReader() = default;

    virtual CardDTO readCardDTO() = 0;
    virtual DeckDTO readDeckDTO() = 0;
    virtual CollectionDTO readCollectionDTO() = 0;

    virtual SnapshotDTO readSnapshotDTO() = 0;
    virtual SessionDTO readSessionDTO() = 0;

    virtual size_t readCount() = 0;
};
