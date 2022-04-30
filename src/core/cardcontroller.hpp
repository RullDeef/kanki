#pragma once

#include <memory>
#include "dbapi/icollectionrepo.hpp"
#include "viewapi/icardview.hpp"
#include "deckcontroller.hpp"

class CardController
{
public:
    CardController(ICardView* view,
        std::shared_ptr<DeckController> deckController,
        Card& card);

    CardController(const CardController&) = delete;
    CardController& operator=(const CardController&) = delete;

    void setSymbol(const std::wstring& value);
    void setReading(const std::wstring& value);
    void setDescription(const std::wstring& value);

    void apply();
    void discard();

private:
    ICardView* view;
    std::shared_ptr<DeckController> deckController;

    Card& activeCard;
    Card initialCard;
};
