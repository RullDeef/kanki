#pragma once

#include "core/iimporter.hpp"

class FileImporter : public IImporter
{
public:
    virtual Collection importCollection(const std::string &filename) override;
};
