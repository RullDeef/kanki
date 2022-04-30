#include "tools/logger.hpp"
#include "card_window.hpp"

CardWindow::CardWindow(std::shared_ptr<ControllerProvider> controllerProvider, const std::string& cardToken)
    : ui(new Ui::CardWindow), cardToken(cardToken)
{
    ui->setupUi(this);
    setModal(true);

    connect(&view, &QtCardView::onShowCard, this, &CardWindow::onShowCard);

    connect(ui->applyButton, &QPushButton::clicked, this, &CardWindow::onApplyChangesButtonPressed);
    connect(ui->discardButton, &QPushButton::clicked, this, &CardWindow::onDiscardChangesBUttonPressed);

    controller = controllerProvider->getCardController(&view, cardToken);
}

CardWindow::~CardWindow()
{
    delete ui;
}

void CardWindow::onShowCard(const CardParams& cardParams)
{
    LOG_METHOD();

    ui->symbolLineEdit->setText(QString::fromStdWString(cardParams.getSymbol()));
    ui->readingLineEdit->setText(QString::fromStdWString(cardParams.getReading()));
    ui->translationLineEdit->setText(QString::fromStdWString(cardParams.getDescription()));
}

void CardWindow::onApplyChangesButtonPressed()
{
    LOG_METHOD();

    controller->setSymbol(ui->symbolLineEdit->text().toStdWString());
    controller->setReading(ui->readingLineEdit->text().toStdWString());
    controller->setDescription(ui->translationLineEdit->toPlainText().toStdWString());

    controller->apply();
    accept();
}

void CardWindow::onDiscardChangesBUttonPressed()
{
    LOG_METHOD();

    controller->discard();
    reject();
}
