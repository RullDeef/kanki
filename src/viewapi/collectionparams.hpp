#pragma once

#include <memory>
#include <list>
#include <map>
#include <string>

#include "model/collection.hpp"

class CollectionParams
{
public:
    CollectionParams(const Collection& collection,
        const std::map<std::string, std::shared_ptr<Deck>>& tokenMap);

    const std::list<std::pair<std::string, Deck::name_type>>& getDeckListInfo() const;

private:
    std::list<std::pair<std::string, Deck::name_type>> deckListInfo;
};
