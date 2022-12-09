#pragma once

#include "model/deck.hpp"

class DeckBuilder
{
public:
    DeckBuilder() = default;

    static DeckBuilder random(size_t cardsCount);

    DeckBuilder &withId(UUID newId);
    DeckBuilder &withName(std::wstring newName);
    DeckBuilder &withCards(std::list<Card> newCards);

    Deck build();

private:
    UUID id;
    std::wstring name;
    std::list<Card> cards;
};
