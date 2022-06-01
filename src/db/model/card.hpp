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
};
