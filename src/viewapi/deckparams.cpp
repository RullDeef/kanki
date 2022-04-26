#include "deckparams.hpp"

DeckParams::DeckParams(const Deck& deck, const TokenMap<std::shared_ptr<Card>>& tokenMap)
    : name(deck.getName())
{
    for (const auto& card : deck)
        cards.emplace_back(tokenMap.getToken(card), CardParams(*card));
}

const Deck::name_type& DeckParams::getName() const
{
    return name;
}

std::list<std::pair<std::string, CardParams>>::const_iterator DeckParams::begin() const
{
    return cards.begin();
}

std::list<std::pair<std::string, CardParams>>::const_iterator DeckParams::end() const
{
    return cards.end();
}
