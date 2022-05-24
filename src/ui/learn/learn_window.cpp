#include "tools/logger.hpp"
#include "learn_window.hpp"

LearnWindow::LearnWindow(LearnerController& controller, QtLearnerView& view)
    : ui(new Ui::LearnWindow), controller(controller)
{
    ui->setupUi(this);
    setModal(true);

    connect(&view, &QtLearnerView::showCardSignal, this, &LearnWindow::onShowCard);
    connect(ui->pushButton, &QPushButton::clicked, this, &LearnWindow::onSubmitButtonPressed);
}

LearnWindow::~LearnWindow()
{
    delete ui;
}

void LearnWindow::onShowCard(const Card& card)
{
    cardId = card.getId();
    ui->symbolLabel->setText(QString::fromStdWString(card.getSymbol()));
    ui->readingLabel->setText(QString::fromStdWString(card.getReading()));
    ui->descriptionLabel->setText(QString::fromStdWString(card.getDescription()));
}

void LearnWindow::onSubmitButtonPressed()
{
    if (cardId != 0)
        controller.confirmLearned(cardId);
    else
        WARN_METHOD("possible error");
    accept();
}
