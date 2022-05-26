#pragma once

#include <fstream>
#include "dto/card.hpp"
#include "dto/deck.hpp"
#include "dto/collection.hpp"

class FileReader
{
public:
    FileReader(std::wifstream& stream);

    CardDTO readCardDTO();
    DeckDTO readDeckDTO();
    CollectionDTO readCollectionDTO();

    size_t readCount();

private:
    std::wifstream& stream;
};
