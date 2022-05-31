#pragma once

#include <string>
#include "model/deckcollection.hpp"

class IExporter
{
public:
    virtual ~IExporter() = default;

    virtual void exportCollection(const std::string &filename, const DeckCollection &collection) = 0;
};
