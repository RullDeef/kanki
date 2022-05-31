#pragma once

#include "core/iioview.hpp"
#include "uiioview.hpp"

class IOViewAdapter : public IIOView
{
public:
    IOViewAdapter(UIIOView &adaptee);

    virtual void showImportedCollection(const DeckCollection& collection) override;
    virtual void showExportStatus(bool success) override;

private:
    UIIOView &adaptee;
};
