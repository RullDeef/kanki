#pragma once

#include <string>
#include "model/collection.hpp"

class IImporter
{
public:
    virtual ~IImporter() = default;

    virtual Collection importCollection(const std::string &filename) = 0;
};
