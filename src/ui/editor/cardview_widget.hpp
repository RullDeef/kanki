#pragma once

#include <QtWidgets/QWidget>
#include "ui_cardview_widget.h"
#include "model/card.hpp"

class CardViewWidget : public QWidget
{
public:
    explicit CardViewWidget(const Card &card);
    ~CardViewWidget();

private:
    Ui::CardViewWidget *ui;
};
