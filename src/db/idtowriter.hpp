#pragma once

#include "dto/card.hpp"
#include "dto/deck.hpp"
#include "dto/collection.hpp"
#include "dto/snapshot.hpp"
#include "dto/session.hpp"

class IDTOWriter
{
public:
    ~IDTOWriter() = default;

    virtual void writeCardDTO(const CardDTO &card) = 0;
    virtual void writeDeckDTO(const DeckDTO &deck) = 0;
    virtual void writeCollectionDTO(const CollectionDTO &collection) = 0;

    virtual void writeSnapshotDTO(const SnapshotDTO &snapshot) = 0;
    virtual void writeSessionDTO(const SessionDTO &session) = 0;

    virtual void writeCount(size_t count) = 0;
};
