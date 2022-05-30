#include <algorithm>
#include "deck.hpp"

Deck::Deck(size_t id, const std::wstring &name)
    : id(id), name(name)
{
}

size_t Deck::getId() const
{
    return id;
}

const std::wstring &Deck::getName() const
{
    return name;
}

void Deck::setName(const std::wstring &newName)
{
    name = newName;
}

size_t Deck::size() const
{
    return cards.size();
}

void Deck::addCard(const Card &card)
{
    size_t id = card.getId();
    auto iter = std::find_if(cards.begin(), cards.end(), [id](const Card &card)
                             { return card.getId() == id; });

    if (iter != cards.end())
        *iter = card;
    else
        cards.push_back(card);
}

const Card *Deck::getCardById(size_t id) const
{
    auto iter = std::find_if(cards.begin(), cards.end(), [id](const Card &card)
                             { return card.getId() == id; });

    if (iter != cards.end())
        return &*iter;
    else
        return nullptr;
}

void Deck::removeCardById(size_t id)
{
    cards.erase(
        std::remove_if(cards.begin(), cards.end(), [id](const Card &card)
                       { return card.getId() == id; }),
        cards.end());
}

Deck::ConstIterator Deck::begin() const
{
    return cards.begin();
}

std::list<Card>::const_iterator Deck::end() const
{
    return cards.end();
}
