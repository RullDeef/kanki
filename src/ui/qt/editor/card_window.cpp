#include "tools/logger.hpp"
#include "card_window.hpp"

CardWindow::CardWindow(std::shared_ptr<EditorController> controller, QtEditorView &view)
    : ui(new Ui::CardWindow), controller(controller)
{
    ui->setupUi(this);
    setModal(true);

    connect(&view, &QtEditorView::showCardSignal, this, &CardWindow::onShowCard);

    connect(ui->applyButton, &QPushButton::clicked, this, &CardWindow::onApplyChangesButtonPressed);
    connect(ui->discardButton, &QPushButton::clicked, this, &CardWindow::onDiscardChangesBUttonPressed);
}

CardWindow::~CardWindow()
{
    delete ui;
}

void CardWindow::onShowCard(const CardParams &card)
{
    LOG_METHOD();

    ui->symbolLineEdit->setText(QString::fromStdWString(card.symbol));
    ui->readingLineEdit->setText(QString::fromStdWString(card.reading));
    ui->translationLineEdit->setText(QString::fromStdWString(card.description));
}

void CardWindow::onApplyChangesButtonPressed()
{
    LOG_METHOD();

    auto symbol = ui->symbolLineEdit->text().toStdWString();
    auto reading = ui->readingLineEdit->text().toStdWString();
    auto description = ui->translationLineEdit->toPlainText().toStdWString();

    controller->setCardSymbol(symbol);
    controller->setCardReading(reading);
    controller->setCardDescription(description);

    controller->saveActiveCard();
    accept();
}

void CardWindow::onDiscardChangesBUttonPressed()
{
    LOG_METHOD();

    controller->rejectActiveCard();
    reject();
}
