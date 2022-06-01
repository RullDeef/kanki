#pragma once

#include <string>
#include "tools/uuid.hpp"

class DBDeckCollection
{
public:
    UUID id;
    std::wstring name;

    bool operator==(const DBDeckCollection &other) const
    {
        return id == other.id && name == other.name;
    }
};
