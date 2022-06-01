#pragma once

#include "model/card.hpp"
#include "model/deck.hpp"
#include "model/deckcollection.hpp"

class IEditorView
{
public:
    virtual ~IEditorView() = default;

    virtual void showCollection(const DeckCollection& collection) = 0;
    virtual void showDeck(const Deck& deck) = 0;
    virtual void showCard(const Card& card) = 0;
};
