#include "tools/logger.hpp"
#include "tools/convertor.hpp"
#include "dbapi/modeladapter.hpp"
#include "collectioncontroller.hpp"
#include "deckcontroller.hpp"

DeckController::DeckController(IDeckView* view,
        std::shared_ptr<CollectionController> collectionController,
        const std::string& deckToken)
    : view(view), collectionController(collectionController),
        activeDeck(collectionController->getDeck(deckToken)),
        initialDeck(collectionController->getDeck(deckToken))
{
    LOG_METHOD();

    view->showDeck(DeckParams(initialDeck));
}

DeckController::~DeckController()
{
    LOG_METHOD();
}

void DeckController::addCard()
{
    LOG_METHOD();
}

void DeckController::editCard(size_t cardIndex)
{
    LOG_METHOD();
}

void DeckController::deleteCard(size_t cardIndex)
{
    LOG_METHOD();

    try
    {
        activeDeck.deleteCard(cardIndex);
        view->showDeck(DeckParams(activeDeck));
    }
    catch(const std::exception& e)
    {
        ERROR_METHOD(e.what());
    }
}

void DeckController::apply()
{
    LOG_METHOD();

    collectionController->confirmEditDeck();
}

void DeckController::discard()
{
    LOG_METHOD();

    activeDeck = initialDeck;

    view->showDeck(DeckParams(activeDeck));
}

void DeckController::setDeckName(const std::string& deckName)
{
    LOG_METHOD();

    activeDeck.setName(deckName);

    view->showDeck(DeckParams(activeDeck));
}


Card& DeckController::getCard(const std::string& cardToken)
{
    LOG_METHOD();

    ///TODO: implement
    return *new Card(L"test1", L"test2", L"test3");
}
