#include "tools/logger.hpp"
#include "dbapi/modeladapter.hpp"
#include "collectioncontroller.hpp"
#include "collectionexporter.hpp"

///TODO: bad code. fix
#include "db/filecollectionrepo.hpp"

CollectionController::CollectionController(ICollectionView* view, std::shared_ptr<ModelManager> modelManager)
    : view(view), modelManager(modelManager)
{
    LOG_METHOD();

    auto collection = modelManager->getCollection();

    tokenMap.clear();
    for (auto deck : *collection)
        tokenMap.insert(deck);

    view->showCollection(CollectionParams(*collection, tokenMap));
}

CollectionController::~CollectionController()
{
    LOG_METHOD();
}

void CollectionController::importCollection(const std::string& filename)
{
    LOG_METHOD();

    ///TODO: fix arch problem (component responsibility & dependency)
    auto collection = CollectionExporter(std::shared_ptr<ICollectionRepository>(
        new FileCollectionRepository(filename)
    )).importCollection();
    
    modelManager->setCollection(collection);

    tokenMap.clear();
    for (auto deck : collection)
        tokenMap.insert(deck);

    view->showCollection(CollectionParams(collection, tokenMap));
}

void CollectionController::exportCollection(const std::string& filename)
{
    LOG_METHOD();

    auto collection = modelManager->getCollection();
    CollectionExporter(std::shared_ptr<ICollectionRepository>(
        new FileCollectionRepository(filename)
    )).exportCollection(*collection);

    LOG_METHOD("collection exported");
}

std::string CollectionController::addDeck()
{
    LOG_METHOD();

    auto collection = modelManager->getCollection();
    auto token = tokenMap.insert(collection->addNewDeck());

    view->showCollection(CollectionParams(*collection, tokenMap));

    return token;
}

void CollectionController::deleteDeck(const std::string& deckToken)
{
    LOG_METHOD();

    auto collection = modelManager->getCollection();
    collection->removeDeck(tokenMap.remove(deckToken));

    view->showCollection(CollectionParams(*collection, tokenMap));
}

Deck& CollectionController::getDeck(const std::string& deckToken)
{
    LOG_METHOD();

    return *tokenMap.get(deckToken);
}

void CollectionController::confirmEditDeck()
{
    LOG_METHOD();

    auto collection = modelManager->getCollection();
    view->showCollection(CollectionParams(*collection, tokenMap));
}
