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
    cards.push_back(std::make_shared<Card>(card));
}

std::shared_ptr<Card> Deck::addNewCard()
{
    return cards.emplace_back(std::make_shared<Card>());
}

void Deck::deleteCard(size_t index)
{
    auto iter = cards.begin();
    std::advance(iter, index);
    cards.erase(iter);
}

void Deck::deleteCard(const std::shared_ptr<Card>& card)
{
    cards.remove(card);
}

size_t Deck::size() const
{
    return cards.size();
}

std::list<std::shared_ptr<Card>>::const_iterator Deck::begin() const
{
    return cards.begin();
}

std::list<std::shared_ptr<Card>>::const_iterator Deck::end() const
{
    return cards.end();
}
