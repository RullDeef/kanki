#pragma once

#include <QtWidgets/QDialog>
#include "core/learnercontroller.hpp"
#include "ui/model/cardparams.hpp"
#include "ui_learn_window.h"

class LearnWindow : public QDialog
{
public:
    LearnWindow(std::shared_ptr<LearnerController> controller, const CardParams &card);
    ~LearnWindow();

protected slots:
    void onSubmitButtonPressed();

private:
    Ui::LearnWindow *ui;

    UUID cardId;
    std::shared_ptr<LearnerController> controller;
};
