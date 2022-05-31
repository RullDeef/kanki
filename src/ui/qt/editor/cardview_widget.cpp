#include "tools/logger.hpp"
#include "cardview_widget.hpp"

CardViewWidget::CardViewWidget(const CardParams &card)
    : ui(new Ui::CardViewWidget)
{
    LOG_METHOD();

    ui->setupUi(this);

    ui->symbolLabel->setText(QString::fromStdWString(card.symbol));
    ui->readingLabel->setText(QString::fromStdWString(card.reading));
    ui->descriptionLabel->setText(QString::fromStdWString(card.description));
}

CardViewWidget::~CardViewWidget()
{
    delete ui;
}
