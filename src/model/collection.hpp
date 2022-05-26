#pragma once

#include <list>
#include "deck.hpp"

class Collection
{
public:
    Collection(size_t id = 0, const std::wstring &name = L"new collection");

    size_t getId() const;
    size_t size() const;

    const std::wstring &getName() const;

    std::list<std::wstring> getDeckNames() const;

    void addDeck(const Deck &deck);

    std::list<Deck>::const_iterator begin() const;
    std::list<Deck>::const_iterator end() const;

    const Deck *getDeckById(size_t id) const;

    void removeDeckById(size_t id);

private:
    size_t id;
    std::wstring name;
    std::list<Deck> decks;
};
