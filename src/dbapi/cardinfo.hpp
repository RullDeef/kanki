#pragma once

#include <string>

class CardInfo
{
public:
    CardInfo(size_t id, size_t deckId, const std::wstring& symbol, const std::wstring& reading, const std::wstring& description)
        : id(id), deckId(deckId), symbol(symbol), reading(reading), description(description) {}

    //TODO: getters

// private:
    size_t id;
    size_t deckId;
    std::wstring symbol;
    std::wstring reading;
    std::wstring description;
};
