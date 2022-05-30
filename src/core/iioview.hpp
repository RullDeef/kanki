#pragma once

#include "model/collection.hpp"

class IIOView
{
public:
    virtual ~IIOView() = default;

    virtual void showImportedCollection(const Collection &collection) = 0;
    virtual void showExportStatus(bool success) = 0;
};
