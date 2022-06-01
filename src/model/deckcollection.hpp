#pragma once

#include <list>
#include "deck.hpp"

class DeckCollection
{
public:
    using ConstIterator = std::list<Deck>::const_iterator;

    DeckCollection(UUID id, const std::wstring &name);

    UUID getId() const;
    size_t size() const;

    const std::wstring &getName() const;

    std::list<std::wstring> getDeckNames() const;

    void addDeck(const Deck &deck);

    ConstIterator begin() const;
    ConstIterator end() const;

    const Deck *getDeckById(UUID id) const;

    void removeDeckById(UUID id);

private:
    UUID id;
    std::wstring name;
    std::list<Deck> decks;
};
