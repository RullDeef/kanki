#pragma once

#include <string>
#include <fstream>
#include "db/idbreader.hpp"

class FileReader : public IDBReader
{
public:
    FileReader(const std::string &filename);

    virtual DBCard readDBCard() override;
    virtual DBDeck readDBDeck() override;
    virtual DBDeckCollection readDBCollection() override;

    virtual DBSnapshot readDBSnapshot() override;
    virtual DBSession readDBSession() override;

    virtual size_t readCount() override;

private:
    std::wifstream stream;
};
