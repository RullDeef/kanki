#pragma once

#include <memory>
#include <string>
#include <QtWidgets/QDialog>
#include "ui_deck_window.h"
#include "qteditorview.hpp"
#include "core/editorcontroller.hpp"

class DeckWindow : public QDialog
{
public:
    DeckWindow(std::shared_ptr<EditorController> controller, QtEditorView &view);
    ~DeckWindow();

protected slots:
    void onShowDeck(const DeckParams &deck);

    void onAddCardButtonPressed();
    void onEditCardButtonPressed();
    void onDeleteCardButtonPressed();
    void onApplyChangesButtonPressed();
    void onDiscardButtonPressed();

private:
    Ui::DeckWindow *ui;
    QtEditorView &view;

    std::shared_ptr<EditorController> controller;
};
