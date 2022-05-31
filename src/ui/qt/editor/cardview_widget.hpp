#pragma once

#include <QtWidgets/QWidget>
#include "ui_cardview_widget.h"
#include "ui/model/cardparams.hpp"

class CardViewWidget : public QWidget
{
public:
    explicit CardViewWidget(const CardParams &card);
    ~CardViewWidget();

private:
    Ui::CardViewWidget *ui;
};
