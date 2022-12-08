#include <algorithm>
#include <stdexcept>
#include "tools/logger.hpp"
#include "deck.hpp"

Deck::Deck(UUID id, const std::wstring &name, std::list<Card> cards)
    : id(id), name(name), cards(std::move(cards))
{
    if (id.is_nil())
    {
        ERROR_METHOD("nil as deck id is not valid");
        throw std::runtime_error("nil as deck id is not valid");
    }
}

UUID Deck::getId() const
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
    auto id = card.getId();
    auto iter = std::find_if(cards.begin(), cards.end(), [id](const Card &card)
                             { return card.getId() == id; });

    if (iter != cards.end())
        *iter = card;
    else
        cards.push_back(card);
}

const Card *Deck::getCardById(UUID id) const
{
    auto iter = std::find_if(cards.begin(), cards.end(), [id](const Card &card)
                             { return card.getId() == id; });

    if (iter != cards.end())
        return &*iter;
    else
        return nullptr;
}

void Deck::removeCardById(UUID id)
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

bool Deck::operator==(const Deck &other) const
{
    return id == other.id && name == other.name && cards == other.cards;
}
