#pragma once

#include <list>
#include <string>
#include "cardparams.hpp"

class DeckParams
{
public:
    UUID id;
    std::wstring name;
    std::list<CardParams> cards;
};
