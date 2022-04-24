#include "tools/logger.hpp"
#include "modelmanager.hpp"
#include "collectionexporter.hpp"

ModelManager::ModelManager(std::shared_ptr<IRepositoryFactory> repoFactory)
    : repoFactory(repoFactory)
{
}

ModelManager::~ModelManager()
{
    LOG_METHOD();

    if (activeCollection)
    {
        CollectionExporter(repoFactory->getCollectionRepo())
            .exportCollection(*activeCollection);    
        LOG_METHOD("collection is exported");
    }
}

// void ModelManager::resetRepoFactory(std::shared_ptr<IRepositoryFactory> newRepoFactory)
// {
//     LOG_METHOD();

//     repoFactory = newRepoFactory;

//     if (activeCollection)
//         *activeCollection = CollectionExporter(repoFactory->getCollectionRepo()).importCollection();
//     else
//         activeCollection = std::make_shared<Collection>(CollectionExporter
//             (repoFactory->getCollectionRepo()).importCollection());

//     *activeSession = Session();
// }

std::shared_ptr<Collection> ModelManager::getCollection()
{
    LOG_METHOD();

    if (!activeCollection)
    {
        LOG_METHOD("active collection is being imported...");

        auto collection = CollectionExporter(repoFactory->getCollectionRepo()).importCollection();
        activeCollection = std::make_shared<Collection>(collection);
    }

    return activeCollection;
}

std::shared_ptr<Session> ModelManager::getActiveSession()
{
    LOG_METHOD();

    if (!activeSession)
    {
        LOG_METHOD("creating new session...");
        activeSession = std::make_shared<Session>();
    }

    return activeSession;
}

std::list<CardSnapshot> ModelManager::getSnapshots(const Card& card)
{
    LOG_METHOD();

    ///TODO: implement
    return {};
}

void ModelManager::setCollection(const Collection& newCollection)
{
    LOG_METHOD();

    *getCollection() = newCollection;
}
