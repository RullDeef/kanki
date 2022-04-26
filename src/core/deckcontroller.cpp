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

    for (const auto& card : activeDeck)
        tokenMap.insert(card);

    view->showDeck(DeckParams(initialDeck, tokenMap));
}

DeckController::~DeckController()
{
    LOG_METHOD();
}

std::string DeckController::addCard()
{
    LOG_METHOD();

    return tokenMap.insert(activeDeck.addNewCard());
}

void DeckController::editCard(const std::string& cardToken)
{
    LOG_METHOD();
}

void DeckController::deleteCard(const std::string& cardToken)
{
    LOG_METHOD();

    TRY_METHOD(
        activeDeck.deleteCard(tokenMap.remove(cardToken));
        view->showDeck(DeckParams(activeDeck, tokenMap));
    );
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
    view->showDeck(DeckParams(activeDeck, tokenMap));
}

void DeckController::setDeckName(const std::string& deckName)
{
    LOG_METHOD();

    activeDeck.setName(deckName);
    view->showDeck(DeckParams(activeDeck, tokenMap));
}


Card& DeckController::getCard(const std::string& cardToken)
{
    LOG_METHOD();

    return *tokenMap.get(cardToken);
}
