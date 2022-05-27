#pragma once

#include <string>

class DeckDTO
{
public:
    size_t id;
    size_t collectionId;
    std::wstring name;

    bool operator==(const DeckDTO &other) const
    {
        return id == other.id && collectionId == other.collectionId && name == other.name;
    }
};
