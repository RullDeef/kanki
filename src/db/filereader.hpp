#pragma once

#include <string>
#include <fstream>
#include "db/idtoreader.hpp"

class FileReader : public IDTOReader
{
public:
    FileReader(const std::string &filename);

    virtual CardDTO readCardDTO() override;
    virtual DeckDTO readDeckDTO() override;
    virtual CollectionDTO readCollectionDTO() override;

    virtual SnapshotDTO readSnapshotDTO() override;
    virtual SessionDTO readSessionDTO() override;

    virtual size_t readCount() override;

private:
    std::wifstream stream;
};
