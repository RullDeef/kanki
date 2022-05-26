#pragma once

#include <fstream>
#include "dto/card.hpp"
#include "dto/deck.hpp"
#include "dto/collection.hpp"
#include "dto/snapshot.hpp"
#include "dto/session.hpp"

class FileReader
{
public:
    FileReader(std::wifstream& stream);

    CardDTO readCardDTO();
    DeckDTO readDeckDTO();
    CollectionDTO readCollectionDTO();

    SnapshotDTO readSnapshotDTO();
    SessionDTO readSessionDTO();

    size_t readCount();

private:
    std::wifstream& stream;
};
