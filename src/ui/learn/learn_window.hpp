#pragma once

#include <QtWidgets/QDialog>
#include "core/learnercontroller.hpp"
#include "ui_learn_window.h"

class LearnWindow : public QDialog
{
public:
    LearnWindow(LearnerController &controller, const Card &card);
    ~LearnWindow();

protected slots:
    void onSubmitButtonPressed();

private:
    Ui::LearnWindow *ui;

    size_t cardId = 0;
    LearnerController &controller;
};
