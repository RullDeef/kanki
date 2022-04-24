#pragma once

#include <memory>
#include "dbapi/icollectionrepo.hpp"
#include "viewapi/icardview.hpp"

class CardController
{
public:
    CardController(ICardView* view, Card& card);

    CardController(const CardController&) = delete;
    CardController& operator=(const CardController&) = delete;

    void setSymbol(const std::wstring& value);
    void setReading(const std::wstring& value);
    void setDescription(const std::wstring& value);

    void apply();
    void discard();

private:
    ICardView* view;

    Card& activeCard;
    Card initialCard;
};
