#include "controllerprovider.hpp"

ControllerProvider::ControllerProvider(std::shared_ptr<IRepositoryFactory> repoFactory)
    : repoFactory(repoFactory), modelManager(new ModelManager(repoFactory))
{
    ///TODO: repo factory is not needed as member
}

std::shared_ptr<CollectionController> ControllerProvider::getCollectionController(ICollectionView* view)
{
    collectionController = std::make_shared<CollectionController>(view, modelManager);
    return collectionController;
}

std::shared_ptr<DeckController> ControllerProvider::getDeckController(IDeckView* view, const std::string& deckToken)
{
    deckController = std::make_shared<DeckController>(view, collectionController, deckToken);
    return deckController;
}

std::shared_ptr<CardController> ControllerProvider::getCardController(ICardView* view, const std::string& cardToken)
{
    return std::make_shared<CardController>(view, deckController, deckController->getCard(cardToken));
}
