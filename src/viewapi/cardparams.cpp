#include "cardparams.hpp"

CardParams::CardParams(const Card& card)
    : symbol(card.getSymbol()), reading(card.getReading()), description(card.getDescription())
{}

const std::wstring& CardParams::getSymbol() const
{
    return symbol;
}

const std::wstring& CardParams::getReading() const
{
    return reading;
}

const std::wstring& CardParams::getDescription() const
{
    return description;
}
