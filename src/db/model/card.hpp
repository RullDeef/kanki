#pragma once

#include <string>
#include "tools/uuid.hpp"

class DBCard
{
public:
    UUID id;
    UUID deckId;
    std::wstring symbol;
    std::wstring reading;
    std::wstring description;

    DBCard() = default;
    DBCard(const DBCard &) = default;
    DBCard(UUID id, UUID deckId, const std::wstring &symbol, const std::wstring &reading, const std::wstring &description)
        : id(id), deckId(deckId), symbol(symbol), reading(reading), description(description) {}
};
