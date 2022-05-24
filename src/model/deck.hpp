#pragma once

#include <algorithm>
#include <list>
#include <string>
#include "card.hpp"

class Deck
{
public:
    Deck(size_t id = 0, const std::wstring& name = L"new deck")
        : id(id), name(name)
    {}

    size_t getId() const { return id; }
    const std::wstring& getName() const { return name; }

    void setName(const std::wstring& newName) { name = newName; }

    size_t size() const { return cards.size(); }

    void addCard(const Card& card) {
        size_t id = card.getId();
        auto iter = std::find_if(cards.begin(), cards.end(),
            [id](const Card& card) { return card.getId() == id; });
        
        if (iter != cards.end())
            *iter = card;
        else
            cards.push_back(card);
    }

    const Card* getCardById(size_t id) {
        auto iter = std::find_if(cards.begin(), cards.end(),
            [id](const Card& card) { return card.getId() == id; });
        
        if (iter != cards.end())
            return &*iter;
        else
            return nullptr;
    }

    void removeCardById(size_t id) {
        std::remove_if(cards.begin(), cards.end(),
            [id](const Card& card) { return card.getId() == id; });
    }

    std::list<Card>::const_iterator begin() const { return cards.begin(); }
    std::list<Card>::const_iterator end() const { return cards.end(); }

private:
    size_t id;
    std::wstring name;
    std::list<Card> cards;
};
