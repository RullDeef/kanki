#pragma once

#include <QObject>
#include "core/ieditorview.hpp"

class QtEditorView : public QObject, public IEditorView
{
    Q_OBJECT

public:
    virtual void showCollection(const Collection& collection);
    virtual void showDeck(const Deck& deck) override;
    virtual void showCard(const Card& card) override;

signals:
    void showCollectionSignal(const Collection& collection);
    void showDeckSignal(const Deck& deck);
    void showCardSignal(const Card& card);
};
