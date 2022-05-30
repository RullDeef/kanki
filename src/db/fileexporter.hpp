#pragma once

#include "core/iexporter.hpp"

class FileExporter : public IExporter
{
public:
    virtual void exportCollection(const std::string &filename, const Collection &collection) override;
};
