#pragma once

#include "core/icollectionmanager.hpp"
#include "core/isessionmanager.hpp"
#include "core/iimporter.hpp"
#include "core/iexporter.hpp"
#include "core/iioview.hpp"

class IOController
{
public:
    IOController(ICollectionManager *collectionManager, ISessionManager *sessionManager);

    void setView(IIOView *newView);

    void setImporter(IImporter *newImporter);
    void setExporter(IExporter *newExporter);

    void exportCollection(const std::string &filename);
    void importCollection(const std::string &filename);

private:
    IIOView *view = nullptr;

    IImporter *importer = nullptr;
    IExporter *exporter = nullptr;

    ICollectionManager *collectionManager;
    ISessionManager *sessionManager;
};
