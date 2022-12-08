#pragma once

#include <list>
#include <string>
#include "card.hpp"

class Deck
{
public:
    using ConstIterator = std::list<Card>::const_iterator;

    Deck(UUID id, const std::wstring &name, std::list<Card> cards = {});

    UUID getId() const;
    size_t size() const;

    const std::wstring &getName() const;
    void setName(const std::wstring &newName);

    void addCard(const Card &card);
    const Card *getCardById(UUID id) const;
    void removeCardById(UUID id);

    ConstIterator begin() const;
    ConstIterator end() const;

    bool operator==(const Deck &other) const;

private:
    UUID id;
    std::wstring name;
    std::list<Card> cards;
};
