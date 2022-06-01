#pragma once

#include <string>
#include "model/deckcollection.hpp"

class IImporter
{
public:
    virtual ~IImporter() = default;

    virtual DeckCollection importCollection(const std::string &filename) = 0;
};
