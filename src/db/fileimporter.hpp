#pragma once

#include "core/iimporter.hpp"

class FileImporter : public IImporter
{
public:
    virtual DeckCollection importCollection(const std::string &filename) override;
};
