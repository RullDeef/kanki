#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "card.hpp"
#include "deck.hpp"

TEST_CASE("card: creation")
{
    Card card(L"symbol", L"reading", L"description");

    CHECK(card.getSymbol() == L"symbol");
    CHECK(card.getReading() == L"reading");
    CHECK(card.getDescription() == L"description");
}

TEST_CASE("deck: insertion")
{
    Deck deck(L"tmp deck");

    CHECK(deck.size() == 0);

    deck.addCard(Card(L"A", L"A", L"A"));
    deck.addCard(Card(L"B", L"B", L"B"));
    deck.addCard(Card(L"C", L"C", L"C"));

    CHECK(deck.size() == 3);
}
