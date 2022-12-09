#include "builder_base.hpp"
#include "cardbuilder.hpp"
#include "deckbuilder.hpp"

DeckBuilder DeckBuilder::random(size_t cardsCount)
{
    std::list<Card> cards;

    for (size_t i = 0; i < cardsCount; ++i)
        cards.push_back(CardBuilder::random().build());

    return DeckBuilder()
        .withId(gen_random_uuid())
        .withName(gen_random_string(20))
        .withCards(cards);
}

DeckBuilder &DeckBuilder::withId(UUID newId)
{
    id = newId;
    return *this;
}

DeckBuilder &DeckBuilder::withName(std::wstring newName)
{
    name = std::move(newName);
    return *this;
}

DeckBuilder &DeckBuilder::withCards(std::list<Card> newCards)
{
    cards = std::move(newCards);
    return *this;
}

Deck DeckBuilder::build()
{
    return Deck(id, name, cards);
}
