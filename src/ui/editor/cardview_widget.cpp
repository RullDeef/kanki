#include "tools/logger.hpp"
#include "cardview_widget.hpp"

CardViewWidget::CardViewWidget(const Card &card)
    : ui(new Ui::CardViewWidget)
{
    LOG_METHOD();

    ui->setupUi(this);

    ui->symbolLabel->setText(QString::fromStdWString(card.getSymbol()));
    ui->readingLabel->setText(QString::fromStdWString(card.getReading()));
    ui->descriptionLabel->setText(QString::fromStdWString(card.getDescription()));
}

CardViewWidget::~CardViewWidget()
{
    delete ui;
}
