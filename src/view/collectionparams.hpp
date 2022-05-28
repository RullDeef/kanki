#pragma once

#include <list>
#include <string>

class CollectionParams
{
public:
    class DeckInfo
    {
    public:
        size_t id;
        std::wstring name;
    };

    std::list<DeckInfo> decks;
};
