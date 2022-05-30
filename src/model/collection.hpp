#pragma once

#include <list>
#include "deck.hpp"

class Collection
{
public:
    using ConstIterator = std::list<Deck>::const_iterator;

    Collection(size_t id = 0, const std::wstring &name = L"new collection");

    size_t getId() const;
    size_t size() const;

    const std::wstring &getName() const;

    std::list<std::wstring> getDeckNames() const;

    void addDeck(const Deck &deck);

    ConstIterator begin() const;
    ConstIterator end() const;

    const Deck *getDeckById(size_t id) const;

    void removeDeckById(size_t id);

private:
    size_t id;
    std::wstring name;
    std::list<Deck> decks;
};
