#pragma once

#include <fstream>
#include "dto/card.hpp"
#include "dto/deck.hpp"
#include "dto/collection.hpp"
#include "dto/snapshot.hpp"
#include "dto/session.hpp"

class FileWriter
{
public:
    FileWriter(std::wofstream &stream);

    void writeCardDTO(const CardDTO &card);
    void writeDeckDTO(const DeckDTO &deck);
    void writeCollectionDTO(const CollectionDTO &collection);

    void writeSnapshotDTO(const SnapshotDTO &snapshot);
    void writeSessionDTO(const SessionDTO &session);

    void writeCount(size_t count);

private:
    std::wofstream &stream;
};
