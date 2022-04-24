#include "tools/logger.hpp"
#include "cardview_widget.hpp"

CardViewWidget::CardViewWidget(const CardParams& cardParams)
    : ui(new Ui::CardViewWidget)
{
    LOG_METHOD();

    ui->setupUi(this);

    ui->symbolLabel->setText(QString::fromStdWString(cardParams.getSymbol()));
    ui->readingLabel->setText(QString::fromStdWString(cardParams.getReading()));
    ui->descriptionLabel->setText(QString::fromStdWString(cardParams.getDescription()));
}

CardViewWidget::~CardViewWidget()
{
    delete ui;
}
