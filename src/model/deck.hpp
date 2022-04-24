#pragma once

#include <list>
#include <string>
#include "card.hpp"

class Deck
{
public:
    using name_type = std::string;

    explicit Deck(const name_type& name = "new Deck");

    const name_type& getName() const;
    void setName(const name_type& newName);

    void addCard(Card&& card);
    void deleteCard(size_t index);

    size_t size() const;

    std::list<Card>::const_iterator begin() const;
    std::list<Card>::const_iterator end() const;

private:
    name_type name;
    std::list<Card> cards;
};
