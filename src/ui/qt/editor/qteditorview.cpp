#include "qteditorview.hpp"

void QtEditorView::showCollection(const CollectionParams &collection)
{
    emit showCollectionSignal(collection);
}

void QtEditorView::showDeck(const DeckParams &deck)
{
    emit showDeckSignal(deck);
}

void QtEditorView::showCard(const CardParams &card)
{
    emit showCardSignal(card);
}
