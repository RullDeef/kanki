#pragma once

#include <QObject>
#include "viewapi/ideckview.hpp"

class QtDeckView : public QObject, public IDeckView
{
    Q_OBJECT

public:
    virtual void showDeck(const DeckParams& deckParams) override;

signals:
    void onShowDeck(const DeckParams& deckParams);
};
