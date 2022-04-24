#pragma once

#include <string>
#include <QtWidgets/QDialog>
#include "ui_deck_window.h"
#include "core/controllerprovider.hpp"
#include "viewapi/deckparams.hpp"
#include "qtdeckview.hpp"

class DeckWindow : public QDialog
{
public:
    DeckWindow(std::shared_ptr<ControllerProvider> controllerProvider, const std::string& deckToken);
    ~DeckWindow();

protected slots:
    void onShowDeck(const DeckParams& deckParams);

    void onAddCardButtonPressed();
    void onEditCardButtonPressed();
    void onDeleteCardButtonPressed();
    void onApplyChangesButtonPressed();
    void onDiscardButtonPressed();

private:
    Ui::DeckWindow *ui;
    QtDeckView view;

    std::string deckToken;
    std::shared_ptr<DeckController> controller;
    std::shared_ptr<ControllerProvider> controllerProvider;
};
