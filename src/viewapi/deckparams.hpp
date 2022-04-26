#pragma once

#include <list>
#include "tools/tokenmap.hpp"
#include "model/deck.hpp"
#include "viewapi/cardparams.hpp"

class DeckParams
{
public:
    DeckParams(const Deck& deck, const TokenMap<std::shared_ptr<Card>>& tokenMap);

    const Deck::name_type& getName() const;

    std::list<std::pair<std::string, CardParams>>::const_iterator begin() const;
    std::list<std::pair<std::string, CardParams>>::const_iterator end() const;

private:
    Deck::name_type name;
    std::list<std::pair<std::string, CardParams>> cards;
};
