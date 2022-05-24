#include "qteditorview.hpp"

void QtEditorView::showCollection(const Collection& collection) {
    emit showCollectionSignal(collection);
}

void QtEditorView::showDeck(const Deck& deck) {
    emit showDeckSignal(deck);
}

void QtEditorView::showCard(const Card& card) {
    emit showCardSignal(card);
}
