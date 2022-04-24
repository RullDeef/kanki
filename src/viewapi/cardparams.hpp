#pragma once

#include "../model/card.hpp"

class CardParams
{
public:
    explicit CardParams(const Card& card);

    const std::wstring& getSymbol() const;
    const std::wstring& getReading() const;
    const std::wstring& getDescription() const;

private:
    std::wstring symbol;
    std::wstring reading;
    std::wstring description;
};
