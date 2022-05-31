#pragma once

#include <QMainWindow>
#include "ui_main_window.h"
#include "core/editorcontroller.hpp"
#include "core/learnercontroller.hpp"
#include "ui/model/editordapter.hpp"
#include "ui/model/learneradapter.hpp"
#include "ui/qt/editor/qteditorview.hpp"
#include "ui/qt/learn/qtlearnerview.hpp"

class MainWindow : public QMainWindow
{
public:
    MainWindow(std::shared_ptr<EditorController> editorController, std::shared_ptr<LearnerController> learnerController);
    ~MainWindow();

protected slots:
    void onShowCollection(const CollectionParams &collection);

    void onAddDeckButtonPressed();
    void onEditDeckButtonPressed();
    void onDeleteDeckButtonPressed();
    void onLearnDeckButtonPressed();
    void onRepeatDeckButtonPressed();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<EditorController> editorController;
    EditorViewAdapter *editorViewAdapter;
    QtEditorView editorView;

    std::shared_ptr<LearnerController> learnerController;
    LearnerViewAdapter *learnerViewAdapter;
    QtLearnerView learnerView;
};
