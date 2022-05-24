#pragma once

#include <algorithm>
#include <list>
#include "deck.hpp"

class Collection
{
public:
    Collection(size_t id = 0, const std::wstring& name = L"new collection")
        : id(id), name(name) {}

    size_t getId() const { return id; }

    const std::wstring& getName() const { return name; }

    size_t size() const { return decks.size(); }

    std::list<std::wstring> getDeckNames() const
    {
        std::list<std::wstring> names(size());
        std::transform(begin(), end(), names.begin(),
            [](const Deck& d) { return d.getName(); });
        return names;
    }

    void addDeck(const Deck& deck) {
        size_t id = deck.getId();
        auto iter = std::find_if(decks.begin(), decks.end(),
            [id](const Deck& deck) { return deck.getId() == id; });
        
        if (iter != decks.end())
            *iter = deck;
        else
            decks.push_back(deck);
    }

    std::list<Deck>::const_iterator begin() const { return decks.begin(); }
    std::list<Deck>::const_iterator end() const { return decks.end(); }    

    const Deck* getDeckById(size_t id) {
        auto iter = std::find_if(begin(), end(), [id](const Deck& deck)
            { return deck.getId() == id; });

        if (iter != end())
            return &*iter;
        return nullptr;
    }

    void removeDeckById(size_t id) {
        decks.erase(
            std::remove_if(decks.begin(), decks.end(),
                [id](const Deck& deck) { return deck.getId() == id; }),
            decks.end());
    }

private:
    size_t id;
    std::wstring name;
    std::list<Deck> decks;
};
