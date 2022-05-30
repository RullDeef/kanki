#pragma once

#include <string>
#include "model/collection.hpp"

class IExporter
{
public:
    virtual ~IExporter() = default;

    virtual void exportCollection(const std::string &filename, const Collection &collection) = 0;
};
