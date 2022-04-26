#include "tools/logger.hpp"
#include "collectionparams.hpp"

CollectionParams::CollectionParams(const Collection& collection, const TokenMap<std::shared_ptr<Deck>>& tokenMap)
{
    for (const auto& deck : collection)
    {
        auto token = tokenMap.getToken(deck);
        deckListInfo.emplace_back(token, deck->getName());
    }
}

const std::list<std::pair<std::string, Deck::name_type>>& CollectionParams::getDeckListInfo() const
{
    return deckListInfo;
}

