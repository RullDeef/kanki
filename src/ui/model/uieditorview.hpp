#pragma once

#include "cardparams.hpp"
#include "deckparams.hpp"
#include "collectionparams.hpp"

class UIEditorView
{
public:
    virtual ~UIEditorView() = default;

    virtual void showCollection(const CollectionParams &params) = 0;
    virtual void showDeck(const DeckParams &params) = 0;
    virtual void showCard(const CardParams &params) = 0;
};
