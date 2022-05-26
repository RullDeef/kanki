#pragma once

#include <string>
#include <fstream>
#include "db/idtowriter.hpp"

class FileWriter : public IDTOWriter
{
public:
    FileWriter(const std::string &filename);

    virtual void writeCardDTO(const CardDTO &card) override;
    virtual void writeDeckDTO(const DeckDTO &deck) override;
    virtual void writeCollectionDTO(const CollectionDTO &collection) override;

    virtual void writeSnapshotDTO(const SnapshotDTO &snapshot) override;
    virtual void writeSessionDTO(const SessionDTO &session) override;

    virtual void writeCount(size_t count) override;

private:
    std::wofstream stream;
};
