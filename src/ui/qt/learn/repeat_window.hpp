#pragma once

#include <memory>
#include <QDialog>
#include "core/learnercontroller.hpp"
#include "qtlearnerview.hpp"
#include "ui_repeat_window.h"

class RepeatWindow : public QDialog
{
public:
    RepeatWindow(std::shared_ptr<LearnerController> controller,
                 QtLearnerView &view, const CardParams &card, int paramType);
    ~RepeatWindow();

protected slots:
    void onShowCardButtonPressed();

    void onEasyButtonPressed();
    void onGoodButtonPressed();
    void onAgainButtonPressed();

private:
    Ui::Dialog *ui;

    CardParams card;
    int paramType;

    std::shared_ptr<LearnerController> controller;
};
