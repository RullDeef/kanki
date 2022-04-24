#pragma once

#include <string>

class DeckInfo
{
public:
    DeckInfo(size_t id, size_t collectionId, const std::string& name)
        : id(id), collectionId(collectionId), name(name) {}

// private:
    size_t id;
    size_t collectionId;
    std::string name;
};
