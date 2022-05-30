#pragma once

#include <list>
#include <string>
#include "card.hpp"

class Deck
{
public:
    using ConstIterator = std::list<Card>::const_iterator;

    Deck(size_t id = 0, const std::wstring &name = L"new deck");

    size_t getId() const;
    size_t size() const;

    const std::wstring &getName() const;
    void setName(const std::wstring &newName);

    void addCard(const Card &card);
    const Card *getCardById(size_t id) const;
    void removeCardById(size_t id);

    ConstIterator begin() const;
    ConstIterator end() const;

private:
    size_t id;
    std::wstring name;
    std::list<Card> cards;
};
