#pragma once

#include <string>
#include "tools/uuid.hpp"

class DBDeck
{
public:
    UUID id;
    UUID collectionId;
    std::wstring name;

    DBDeck() = default;
    DBDeck(const DBDeck &) = default;

    DBDeck(UUID id, UUID collectionId, const std::wstring &name)
        : id(id), collectionId(collectionId), name(name) {}

    bool operator==(const DBDeck &other) const
    {
        return id == other.id && collectionId == other.collectionId && name == other.name;
    }
};
