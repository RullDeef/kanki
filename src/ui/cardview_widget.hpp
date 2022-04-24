#pragma once

#include <QtWidgets/QWidget>
#include "ui_cardview_widget.h"
#include "viewapi/cardparams.hpp"

class CardViewWidget : public QWidget
{
public:
    explicit CardViewWidget(const CardParams& cardParams);
    ~CardViewWidget();

private:
    Ui::CardViewWidget *ui;
};
