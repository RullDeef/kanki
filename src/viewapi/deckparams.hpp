#pragma once

#include <list>
#include "model/deck.hpp"
#include "viewapi/cardparams.hpp"

class DeckParams
{
public:
    DeckParams();
    explicit DeckParams(const Deck& deck);

    const Deck::name_type& getName() const;

    std::list<CardParams>::const_iterator begin() const;
    std::list<CardParams>::const_iterator end() const;

private:
    Deck::name_type name;
    std::list<CardParams> cards;
};
