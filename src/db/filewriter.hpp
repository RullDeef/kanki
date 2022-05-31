#pragma once

#include <string>
#include <fstream>
#include "db/idtowriter.hpp"

class FileWriter : public IDTOWriter
{
public:
    FileWriter(const std::string &filename);

    virtual void writeCardDTO(const DBCard &card) override;
    virtual void writeDeckDTO(const DBDeck &deck) override;
    virtual void writeCollectionDTO(const DBDeckCollection &collection) override;

    virtual void writeSnapshotDTO(const DBSnapshot &snapshot) override;
    virtual void writeSessionDTO(const SessionDTO &session) override;

    virtual void writeCount(size_t count) override;

private:
    std::wofstream stream;
};
