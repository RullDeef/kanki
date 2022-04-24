#include "deck.hpp"

Deck::Deck(const name_type& name)
    : name(name)
{}

const Deck::name_type& Deck::getName() const
{
    return name;
}

void Deck::setName(const name_type& newName)
{
    name = newName;
}

void Deck::addCard(Card&& card)
{
    cards.push_back(card);
}

void Deck::deleteCard(size_t index)
{
    auto iter = cards.begin();
    std::advance(iter, index);
    cards.erase(iter);
}

size_t Deck::size() const
{
    return cards.size();
}

std::list<Card>::const_iterator Deck::begin() const
{
    return cards.begin();
}

std::list<Card>::const_iterator Deck::end() const
{
    return cards.end();
}
