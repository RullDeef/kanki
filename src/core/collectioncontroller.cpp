#include "tools/logger.hpp"
#include "tools/token.hpp"
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
    {
        auto token = TokenGenerator::generate();
        tokenMap[token] = deck;
    }

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
    {
        auto token = TokenGenerator::generate();
        tokenMap[token] = deck;
    }

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

    auto token = TokenGenerator::generate();
    auto collection = modelManager->getCollection();
    tokenMap[token] = collection->addNewDeck();

    view->showCollection(CollectionParams(*collection, tokenMap));

    return token;
}

void CollectionController::deleteDeck(const std::string& deckToken)
{
    LOG_METHOD();

    auto collection = modelManager->getCollection();
    collection->removeDeck(tokenMap[deckToken]);
    tokenMap.erase(deckToken);

    view->showCollection(CollectionParams(*collection, tokenMap));
}

Deck& CollectionController::getDeck(const std::string& deckToken)
{
    LOG_METHOD();

    return *tokenMap[deckToken];
}

void CollectionController::confirmEditDeck()
{
    LOG_METHOD();

    auto collection = modelManager->getCollection();
    view->showCollection(CollectionParams(*collection, tokenMap));
}
