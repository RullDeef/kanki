#include "tools/logger.hpp"
#include "iocontroller.hpp"

IOController::IOController(std::shared_ptr<ICollectionManager> collectionManager, std::shared_ptr<ISessionManager> sessionManager)
    : collectionManager(collectionManager), sessionManager(sessionManager)
{
}

void IOController::setView(IIOView *newView)
{
    view = newView;
}

void IOController::setImporter(std::shared_ptr<IImporter> newImporter)
{
    importer = newImporter;
}

void IOController::setExporter(std::shared_ptr<IExporter> newExporter)
{
    exporter = newExporter;
}

void IOController::exportCollection(const std::string &filename)
{
    LOG_METHOD("filename=" + filename);

    if (exporter == nullptr)
    {
        ERROR_METHOD("exporter not set");
        if (view != nullptr)
            view->showExportStatus(false);
        return;
    }

    try
    {
        exporter->exportCollection(filename, collectionManager->getActiveCollection());

        if (view != nullptr)
            view->showExportStatus(true);
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD(e.what());

        if (view != nullptr)
            view->showExportStatus(false);
    }
}

void IOController::importCollection(const std::string &filename)
{
    LOG_METHOD("filename=" + filename);

    if (exporter == nullptr)
    {
        ERROR_METHOD("importer not set");
        return;
    }

    try
    {
        auto collection = importer->importCollection(filename);
        collectionManager->saveCollection(collection);
        if (view != nullptr)
            view->showImportedCollection(collection);
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD(e.what());
    }
}
