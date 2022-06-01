#pragma once

#include <string>
#include <fstream>
#include "db/idbwriter.hpp"

class FileWriter : public IDBWriter
{
public:
    FileWriter(const std::string &filename);

    virtual void writeDBCard(const DBCard &card) override;
    virtual void writeDBDeck(const DBDeck &deck) override;
    virtual void writeDBCollection(const DBDeckCollection &collection) override;

    virtual void writeDBSnapshot(const DBSnapshot &snapshot) override;
    virtual void writeDBSession(const DBSession &session) override;

    virtual void writeCount(size_t count) override;

private:
    std::wofstream stream;
};
