#pragma once

#include <QtWidgets/QDialog>
#include "core/learnercontroller.hpp"
#include "ui/learn/qtlearnerview.hpp"
#include "ui_learn_window.h"

class LearnWindow : public QDialog
{
public:
    LearnWindow(LearnerController& controller, QtLearnerView& view);
    ~LearnWindow();

protected slots:
    void onShowCard(const Card& card);

    void onSubmitButtonPressed();

private:
    Ui::LearnWindow* ui;

    size_t cardId = 0;
    LearnerController& controller;
};
