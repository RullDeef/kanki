#include "deckparams.hpp"

DeckParams::DeckParams()
    : name("New Deck")
{}

DeckParams::DeckParams(const Deck& deck)
    : name(deck.getName())
{
    for (const auto& card : deck)
        cards.push_back(CardParams(card));
}

const Deck::name_type& DeckParams::getName() const
{
    return name;
}

std::list<CardParams>::const_iterator DeckParams::begin() const
{
    return cards.begin();
}

std::list<CardParams>::const_iterator DeckParams::end() const
{
    return cards.end();
}
