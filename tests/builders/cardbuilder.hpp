#pragma once

#include "model/card.hpp"

class CardBuilder
{
public:
    CardBuilder() = default;

    static CardBuilder random();

    CardBuilder &withId(UUID newId);
    CardBuilder &withSymbol(std::wstring newSymbol);
    CardBuilder &withReading(std::wstring newReading);
    CardBuilder &withDescription(std::wstring newDescription);

    Card build();

private:
    UUID id;
    std::wstring symbol;
    std::wstring reading;
    std::wstring description;
};
