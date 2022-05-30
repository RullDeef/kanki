#include "ioviewadapter.hpp"
#include "convertor.hpp"

IOViewAdapter::IOViewAdapter(UIIOView &adaptee)
    : adaptee(adaptee)
{
}

void IOViewAdapter::showImportedCollection(const Collection &collection)
{
    auto params = ParamsConvertor().toCollectionParams(collection);
    adaptee.showImportedCollection(params);
}

void IOViewAdapter::showExportStatus(bool success)
{
    adaptee.showExportStatus(success);
}
