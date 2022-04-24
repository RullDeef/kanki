#pragma once

#include <QMainWindow>
#include "core/controllerprovider.hpp"
#include "qtcollectionview.hpp"
#include "ui_main_window.h"

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(std::shared_ptr<ControllerProvider> controllerProvider);

    ~MainWindow();

protected slots:
    void onShowCollection(const CollectionParams& collectionParams);

    void onAddDeckButtonPressed();
    void onEditDeckButtonPressed();
    void onLearnDeckButtonPressed();
    void onRepeatDeckButtonPressed();
    void onDeleteDeckButtonPressed();

private:
    Ui::MainWindow* ui;
    QtCollectionView view;

    std::shared_ptr<CollectionController> controller;
    std::shared_ptr<ControllerProvider> controllerProvider;
};
