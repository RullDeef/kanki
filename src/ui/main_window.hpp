#pragma once

#include <QMainWindow>
#include "ui_main_window.h"
#include "core/editorcontroller.hpp"
#include "qteditorview.hpp"

class MainWindow : public QMainWindow
{
public:
    MainWindow(EditorController& controller);
    ~MainWindow();

protected slots:
    void onShowCollection(const Collection& collection);

    void onAddDeckButtonPressed();
    void onEditDeckButtonPressed();
    void onLearnDeckButtonPressed();
    void onRepeatDeckButtonPressed();
    void onDeleteDeckButtonPressed();

private:
    Ui::MainWindow* ui;

    QtEditorView view;
    EditorController& controller;
};
