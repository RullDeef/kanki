#pragma once

#include <memory>
#include <list>
#include "deck.hpp"

class Collection
{
public:
    std::shared_ptr<Deck> addNewDeck();
    void removeDeck(const std::shared_ptr<Deck>& deck);

    size_t size() const;

    std::list<Deck::name_type> getDeckNames() const;

    std::list<std::shared_ptr<Deck>>::const_iterator begin() const;
    std::list<std::shared_ptr<Deck>>::const_iterator end() const;

private:
    std::list<std::shared_ptr<Deck>> decks;
};
