#pragma once

#include <QObject>
#include "ui/model/uieditorview.hpp"

class QtEditorView : public QObject, public UIEditorView
{
    Q_OBJECT

public:
    virtual void showCollection(const CollectionParams &params) override;
    virtual void showDeck(const DeckParams &params) override;
    virtual void showCard(const CardParams &params) override;

signals:
    void showCollectionSignal(const CollectionParams &collection);
    void showDeckSignal(const DeckParams &deck);
    void showCardSignal(const CardParams &card);
};
