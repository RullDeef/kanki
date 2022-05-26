#include "info_window.hpp"

InfoWindow::InfoWindow(const char* message)
    : ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
    setModal(true);

    connect(ui->actionButton, &QPushButton::clicked, this, &InfoWindow::closeWindow);

    ui->infoLabel->setText(message);
}

InfoWindow::~InfoWindow()
{
    delete ui;
}

void InfoWindow::closeWindow()
{
    accept();
}
