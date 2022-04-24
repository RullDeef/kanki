#include "tools/logger.hpp"
#include "collectionparams.hpp"

CollectionParams::CollectionParams(const Collection& collection,
        const std::map<std::string, std::shared_ptr<Deck>>& tokenMap)
{
    for (const auto& deck : collection)
    {
        auto it = std::find_if(tokenMap.begin(), tokenMap.end(), [&deck]
            (const std::pair<std::string, std::shared_ptr<Deck>>& pair) {
                return deck == pair.second;
            });
        
        if (it == tokenMap.end())
            ERROR_METHOD("token not found");
        else
            deckListInfo.emplace_back(std::pair<std::string, Deck::name_type>(it->first, deck->getName()));
    }
}

const std::list<std::pair<std::string, Deck::name_type>>& CollectionParams::getDeckListInfo() const
{
    return deckListInfo;
}

