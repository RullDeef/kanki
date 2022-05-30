#pragma once

#include "collectionparams.hpp"

class UIIOView
{
public:
    virtual ~UIIOView() = default;

    virtual void showImportedCollection(const CollectionParams &params) = 0;
    virtual void showExportStatus(bool success) = 0;
};
