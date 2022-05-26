#pragma once

#include <QDialog>
#include "ui_info_window.h"

class InfoWindow : public QDialog
{
    Q_OBJECT

public:
    InfoWindow(const char* message);
    ~InfoWindow();

protected slots:
    void closeWindow();

private:
    Ui::InfoWindow* ui;
};
