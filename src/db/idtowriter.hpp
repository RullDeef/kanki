#pragma once

#include "db/model/card.hpp"
#include "db/model/deck.hpp"
#include "db/model/collection.hpp"
#include "db/model/snapshot.hpp"
#include "db/model/session.hpp"

class IDTOWriter
{
public:
    ~IDTOWriter() = default;

    virtual void writeCardDTO(const DBCard &card) = 0;
    virtual void writeDeckDTO(const DBDeck &deck) = 0;
    virtual void writeCollectionDTO(const DBDeckCollection &collection) = 0;

    virtual void writeSnapshotDTO(const DBSnapshot &snapshot) = 0;
    virtual void writeSessionDTO(const DBSession &session) = 0;

    virtual void writeCount(size_t count) = 0;
};
