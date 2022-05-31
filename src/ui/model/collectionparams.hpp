#pragma once

#include <list>
#include <string>
#include "tools/uuid.hpp"

class CollectionParams
{
public:
    class DeckInfo
    {
    public:
        UUID id;
        std::wstring name;
    };

    std::list<DeckInfo> decks;
};
