#pragma once

#include <QMainWindow>
#include "ui_main_window.h"
#include "core/editorcontroller.hpp"
#include "core/learnercontroller.hpp"
#include "ui/editor/qteditorview.hpp"
#include "ui/learn/qtlearnerview.hpp"

class MainWindow : public QMainWindow
{
public:
    MainWindow(EditorController &editorController, LearnerController &learnerController);
    ~MainWindow();

protected slots:
    void onShowCollection(const Collection &collection);

    void onAddDeckButtonPressed();
    void onEditDeckButtonPressed();
    void onDeleteDeckButtonPressed();
    void onLearnDeckButtonPressed();
    void onRepeatDeckButtonPressed();

private:
    Ui::MainWindow *ui;

    QtEditorView editorView;
    QtLearnerView learnerView;
    EditorController &editorController;
    LearnerController &learnerController;
};
