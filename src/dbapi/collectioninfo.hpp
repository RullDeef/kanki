#pragma once

#include <string>

class CollectionInfo
{
public:
    CollectionInfo(size_t id, const std::string& name)
        : id(id), name(name) {}

    //TODO: create geters...

//TODO: ...and make this private
// private:
    size_t id;
    std::string name;
};
