#pragma once

#include <string>
#include "tools/uuid.hpp"

class CardParams
{
public:
    UUID id;
    std::wstring symbol;
    std::wstring reading;
    std::wstring description;
};
