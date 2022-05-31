#pragma once

#include "model/deckcollection.hpp"

class IIOView
{
public:
    virtual ~IIOView() = default;

    virtual void showImportedCollection(const DeckCollection &collection) = 0;
    virtual void showExportStatus(bool success) = 0;
};
