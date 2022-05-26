#pragma once

#include <string>

class CardDTO
{
public:
    size_t id;
    size_t deckId;
    std::wstring symbol;
    std::wstring reading;
    std::wstring description;
};
