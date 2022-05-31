#pragma once

#include <string>
#include <fstream>
#include "db/idtoreader.hpp"

class FileReader : public IDTOReader
{
public:
    FileReader(const std::string &filename);

    virtual DBCard readCardDTO() override;
    virtual DBDeck readDeckDTO() override;
    virtual DBDeckCollection readCollectionDTO() override;

    virtual DBSnapshot readSnapshotDTO() override;
    virtual DBSession readSessionDTO() override;

    virtual size_t readCount() override;

private:
    std::wifstream stream;
};
