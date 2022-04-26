#pragma once

#include <memory>
#include <list>
#include <string>
#include "tools/tokenmap.hpp"
#include "model/collection.hpp"

class CollectionParams
{
public:
    CollectionParams(const Collection& collection, const TokenMap<std::shared_ptr<Deck>>& tokenMap);

    const std::list<std::pair<std::string, Deck::name_type>>& getDeckListInfo() const;

private:
    std::list<std::pair<std::string, Deck::name_type>> deckListInfo;
};
