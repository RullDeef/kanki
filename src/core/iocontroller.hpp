#pragma once

#include <memory>
#include "core/icollectionmanager.hpp"
#include "core/isessionmanager.hpp"
#include "core/iimporter.hpp"
#include "core/iexporter.hpp"
#include "core/iioview.hpp"

class IOController
{
public:
    IOController(std::shared_ptr<ICollectionManager> collectionManager, std::shared_ptr<ISessionManager> sessionManager);

    void setView(IIOView *newView);

    void setImporter(std::shared_ptr<IImporter> newImporter);
    void setExporter(std::shared_ptr<IExporter> newExporter);

    void exportCollection(const std::string &filename);
    void importCollection(const std::string &filename);

private:
    IIOView *view = nullptr;

    std::shared_ptr<IImporter> importer;
    std::shared_ptr<IExporter> exporter;

    std::shared_ptr<ICollectionManager> collectionManager;
    std::shared_ptr<ISessionManager> sessionManager;
};
