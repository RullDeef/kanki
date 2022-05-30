#include "editordapter.hpp"
#include "convertor.hpp"

EditorViewAdapter::EditorViewAdapter(UIEditorView &adaptee)
    : adaptee(adaptee)
{
}

void EditorViewAdapter::showCollection(const Collection &collection)
{
    auto params = ParamsConvertor().toCollectionParams(collection);
    adaptee.showCollection(params);
}

void EditorViewAdapter::showDeck(const Deck &deck)
{
    auto params = ParamsConvertor().toDeckParams(deck);
    adaptee.showDeck(params);
}

void EditorViewAdapter::showCard(const Card &card)
{
    auto params = ParamsConvertor().toCardParams(card);
    adaptee.showCard(params);
}
