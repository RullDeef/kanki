#include "tools/logger.hpp"
#include "cardcontroller.hpp"

CardController::CardController(ICardView* view,
        std::shared_ptr<DeckController> deckController, Card& card)
    : view(view), deckController(deckController), activeCard(card), initialCard(card)
{
    LOG_METHOD();
    
    view->showCard(CardParams(card));
}

void CardController::setSymbol(const std::wstring& value)
{
    LOG_METHOD();
    
    activeCard.setSymbol(value);
}

void CardController::setReading(const std::wstring& value)
{
    LOG_METHOD();
    
    activeCard.setReading(value);
}

void CardController::setDescription(const std::wstring& value)
{
    LOG_METHOD();
    
    activeCard.setDescription(value);
}

void CardController::apply()
{
    LOG_METHOD();

    deckController->confirmEditCard();
}

void CardController::discard()
{
    LOG_METHOD();

    activeCard = initialCard;

    deckController->confirmEditCard();
}

