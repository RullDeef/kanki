#pragma once

#include "model/deckcollection.hpp"

class DeckCollectionBuilder
{
public:
    DeckCollectionBuilder() = default;

    static DeckCollectionBuilder random(size_t decksCount, size_t cardsCount);

    DeckCollectionBuilder& withId(UUID newId);
    DeckCollectionBuilder& withName(std::wstring newName);
    DeckCollectionBuilder& withDecks(std::list<Deck> newDecks);

    DeckCollection build();

private:
    UUID id;
    std::wstring name;
    std::list<Deck> decks;
};
