#pragma once

#include <string>
#include "tools/uuid.hpp"

class DBDeck
{
public:
    UUID id;
    UUID collectionId;
    std::wstring name;

    bool operator==(const DBDeck &other) const
    {
        return id == other.id && collectionId == other.collectionId && name == other.name;
    }
};
