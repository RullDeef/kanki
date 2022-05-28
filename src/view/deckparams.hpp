#pragma once

#include <list>
#include <string>
#include "cardparams.hpp"

class DeckParams
{
public:
    size_t id;
    std::wstring name;
    std::list<CardParams> cards;
};
