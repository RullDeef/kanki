#include "qtdeckview.hpp"

void QtDeckView::showDeck(const DeckParams& deckParams)
{
    emit onShowDeck(deckParams);
}
