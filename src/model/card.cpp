#include "card.hpp"

Card::Card(size_t id,
           const std::wstring &symbol,
           const std::wstring &reading,
           const std::wstring &description)
    : id(id), symbol(symbol), reading(reading), description(description)
{
}

const size_t Card::getId() const
{
    return id;
}

const std::wstring &Card::getSymbol() const
{
    return symbol;
}

const std::wstring &Card::getReading() const
{
    return reading;
}

const std::wstring &Card::getDescription() const
{
    return description;
}

void Card::setSymbol(const std::wstring &value)
{
    symbol = value;
}

void Card::setReading(const std::wstring &value)
{
    reading = value;
}

void Card::setDescription(const std::wstring &value)
{
    description = value;
}

bool Card::operator==(const Card &other) const
{
    return symbol == other.symbol &&
           reading == other.reading &&
           description == other.description;
}
