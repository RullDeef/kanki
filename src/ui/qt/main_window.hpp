#pragma once

#include <QMainWindow>
#include "ui_main_window.h"
#include "core/editorcontroller.hpp"
#include "core/learnercontroller.hpp"
#include "core/iocontroller.hpp"
#include "ui/model/editordapter.hpp"
#include "ui/model/learneradapter.hpp"
#include "ui/model/ioviewadapter.hpp"
#include "ui/qt/editor/qteditorview.hpp"
#include "ui/qt/learn/qtlearnerview.hpp"
#include "ui/qt/qtioview.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<EditorController> editorController,
        std::shared_ptr<LearnerController> learnerController,
        std::shared_ptr<IOController> ioController);
    ~MainWindow();

protected slots:
    void onShowCollection(const CollectionParams &collection);

    void onAddDeckButtonPressed();
    void onEditDeckButtonPressed();
    void onDeleteDeckButtonPressed();
    void onLearnDeckButtonPressed();
    void onRepeatDeckButtonPressed();

    void onImportAction();
    void onExportAction();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<EditorController> editorController;
    EditorViewAdapter *editorViewAdapter;
    QtEditorView editorView;

    std::shared_ptr<LearnerController> learnerController;
    LearnerViewAdapter *learnerViewAdapter;
    QtLearnerView learnerView;

    std::shared_ptr<IOController> ioController;
    IOViewAdapter *ioViewAdapter;
    QtIOView ioView;
};
