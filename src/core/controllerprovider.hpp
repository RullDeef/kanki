#pragma once

#include <memory>
#include "viewapi/icardview.hpp"
#include "viewapi/ideckview.hpp"
#include "viewapi/icollectionview.hpp"
#include "dbapi/irepofactory.hpp"
#include "cardcontroller.hpp"
#include "deckcontroller.hpp"
#include "collectioncontroller.hpp"
#include "modelmanager.hpp"

class ControllerProvider
{
public:
    explicit ControllerProvider(std::shared_ptr<IRepositoryFactory> repoFactory);

    std::shared_ptr<CollectionController> getCollectionController(ICollectionView* view);
    std::shared_ptr<DeckController> getDeckController(IDeckView* view, const std::string& deckToken);
    std::shared_ptr<CardController> getCardController(ICardView* view, const std::string& cardToken);

private:
    std::shared_ptr<IRepositoryFactory> repoFactory;
    std::shared_ptr<ModelManager> modelManager;
    std::shared_ptr<CollectionController> collectionController;
    std::shared_ptr<DeckController> deckController;
};
