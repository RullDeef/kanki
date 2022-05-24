#pragma once

#include <memory>
#include <string>
#include <QtWidgets/QDialog>
#include "core/editorcontroller.hpp"
#include "qteditorview.hpp"
#include "ui_card_window.h"

class CardWindow : public QDialog
{
public:
    CardWindow(EditorController& controller, QtEditorView& view);
    ~CardWindow();

protected slots:
    void onShowCard(const Card& cardParams);

    ///TODO: apply with ctrl+Enter
    void onApplyChangesButtonPressed();
    void onDiscardChangesBUttonPressed();

private:
    Ui::CardWindow *ui;

    EditorController& controller;
};
