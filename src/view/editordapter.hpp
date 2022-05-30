#pragma once

#include "core/ieditorview.hpp"
#include "uieditorview.hpp"

class EditorViewAdapter : public IEditorView
{
public:
    EditorViewAdapter(UIEditorView &adaptee);

    virtual void showCollection(const Collection &collection) override;
    virtual void showDeck(const Deck &deck) override;
    virtual void showCard(const Card &card) override;

private:
    UIEditorView &adaptee;
};
