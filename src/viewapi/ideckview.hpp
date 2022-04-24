#pragma once

#include <list>
#include <string>
#include "viewapi/deckparams.hpp"

class IDeckView
{
public:
    virtual ~IDeckView() = default;

    virtual void showDeck(const DeckParams& deckParams) = 0;
};
