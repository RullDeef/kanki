#pragma once

#include <string>
#include "tools/uuid.hpp"

class DBDeckCollection
{
public:
    UUID id;
    std::wstring name;

    DBDeckCollection() = default;
    DBDeckCollection(const DBDeckCollection &) = default;
    DBDeckCollection(UUID id, const std::wstring &name)
        : id(id), name(name) {}

    bool operator==(const DBDeckCollection &other) const
    {
        return id == other.id && name == other.name;
    }
};
