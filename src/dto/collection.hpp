#pragma once

#include <string>

class CollectionDTO
{
public:
    size_t id;
    std::wstring name;

    bool operator==(const CollectionDTO &other) const
    {
        return id == other.id && name == other.name;
    }
};
