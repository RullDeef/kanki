#pragma once

#include <memory>
#include <string>
#include <QtWidgets/QDialog>
#include "viewapi/cardparams.hpp"
#include "core/controllerprovider.hpp"
#include "qtcardview.hpp"
#include "ui_card_window.h"

class CardWindow : public QDialog
{
public:
    CardWindow(std::shared_ptr<ControllerProvider> controllerProvider, const std::string& cardToken);
    ~CardWindow();

protected slots:
    void onShowCard(const CardParams& cardParams);

    ///TODO: apply with ctrl+Enter
    void onApplyChangesButtonPressed();
    void onDiscardChangesBUttonPressed();

private:
    Ui::CardWindow *ui;
    QtCardView view;

    std::string cardToken;
    std::shared_ptr<CardController> controller;
};
