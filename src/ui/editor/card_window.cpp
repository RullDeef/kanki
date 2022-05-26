#include "tools/logger.hpp"
#include "card_window.hpp"

CardWindow::CardWindow(EditorController &controller, QtEditorView &view)
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

void CardWindow::onShowCard(const Card &card)
{
    LOG_METHOD();

    ui->symbolLineEdit->setText(QString::fromStdWString(card.getSymbol()));
    ui->readingLineEdit->setText(QString::fromStdWString(card.getReading()));
    ui->translationLineEdit->setText(QString::fromStdWString(card.getDescription()));
}

void CardWindow::onApplyChangesButtonPressed()
{
    LOG_METHOD();

    controller.setCardSymbol(ui->symbolLineEdit->text().toStdWString());
    controller.setCardReading(ui->readingLineEdit->text().toStdWString());
    controller.setCardDescription(ui->translationLineEdit->toPlainText().toStdWString());

    controller.saveActiveCard();
    accept();
}

void CardWindow::onDiscardChangesBUttonPressed()
{
    LOG_METHOD();

    controller.rejectActiveCard();
    reject();
}
