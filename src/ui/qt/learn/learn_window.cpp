#include "tools/logger.hpp"
#include "learn_window.hpp"

LearnWindow::LearnWindow(std::shared_ptr<LearnerController> controller, const CardParams &card)
    : ui(new Ui::LearnWindow), controller(controller), cardId(card.id)
{
    ui->setupUi(this);
    setModal(true);

    ui->symbolLabel->setText(QString::fromStdWString(card.symbol));
    ui->readingLabel->setText(QString::fromStdWString(card.reading));
    ui->descriptionLabel->setText(QString::fromStdWString(card.description));

    connect(ui->pushButton, &QPushButton::clicked, this, &LearnWindow::onSubmitButtonPressed);
}

LearnWindow::~LearnWindow()
{
    delete ui;
}

void LearnWindow::onSubmitButtonPressed()
{
    controller->confirmLearned(cardId);
    accept();
}
