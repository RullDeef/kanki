#include "builder_base.hpp"
#include "cardbuilder.hpp"
#include "deckbuilder.hpp"
#include "collectionbuilder.hpp"

DeckCollectionBuilder DeckCollectionBuilder::random(size_t decksCount, size_t cardsCount)
{
    std::list<Deck> decks;

    for (size_t i = 0; i < decksCount; ++i)
        decks.push_back(DeckBuilder::random(cardsCount).build());

    return DeckCollectionBuilder()
        .withId(gen_random_uuid())
        .withName(gen_random_string(20))
        .withDecks(decks);
}

DeckCollectionBuilder &DeckCollectionBuilder::withId(UUID newId)
{
    id = newId;
    return *this;
}

DeckCollectionBuilder &DeckCollectionBuilder::withName(std::wstring newName)
{
    name = std::move(newName);
    return *this;
}

DeckCollectionBuilder &DeckCollectionBuilder::withDecks(std::list<Deck> newDecks)
{
    decks = std::move(newDecks);
    return *this;
}

DeckCollection DeckCollectionBuilder::build()
{
    return DeckCollection(id, name, decks);
}
