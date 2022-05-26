#include "tools/logger.hpp"
#include "learn_window.hpp"

LearnWindow::LearnWindow(LearnerController &controller, const Card &card)
    : ui(new Ui::LearnWindow), controller(controller)
{
    ui->setupUi(this);
    setModal(true);

    cardId = card.getId();
    ui->symbolLabel->setText(QString::fromStdWString(card.getSymbol()));
    ui->readingLabel->setText(QString::fromStdWString(card.getReading()));
    ui->descriptionLabel->setText(QString::fromStdWString(card.getDescription()));

    connect(ui->pushButton, &QPushButton::clicked, this, &LearnWindow::onSubmitButtonPressed);
}

LearnWindow::~LearnWindow()
{
    delete ui;
}

void LearnWindow::onSubmitButtonPressed()
{
    controller.confirmLearned(cardId);
    accept();
}
