#include "repeat_window.hpp"

RepeatWindow::RepeatWindow(std::shared_ptr<LearnerController> controller,
                           QtLearnerView &view, const CardParams &card, int paramType)
    : ui(new Ui::Dialog), card(card), paramType(paramType), controller(controller)
{
    ui->setupUi(this);

    ui->symbolLabel->setText(QString::fromStdWString(card.symbol));
    if (paramType == Snapshot::ParamType::READING)
        ui->visibleLabel->setText(QString::fromStdWString(card.description));
    else
        ui->visibleLabel->setText(QString::fromStdWString(card.reading));
    ui->hiddenLabel->setText("?");

    connect(ui->easyButton, &QPushButton::pressed, this, &RepeatWindow::onEasyButtonPressed);
    connect(ui->goodButton, &QPushButton::pressed, this, &RepeatWindow::onGoodButtonPressed);
    connect(ui->againButton, &QPushButton::pressed, this, &RepeatWindow::onAgainButtonPressed);
    connect(ui->showCardButton, &QPushButton::pressed, this, &RepeatWindow::onShowCardButtonPressed);
}

RepeatWindow::~RepeatWindow()
{
    delete ui;
}

void RepeatWindow::onShowCardButtonPressed()
{
    ui->showCardButton->setEnabled(false);
    ui->easyButton->setEnabled(true);
    ui->goodButton->setEnabled(true);
    ui->againButton->setEnabled(true);

    if (paramType == Snapshot::ParamType::READING)
        ui->hiddenLabel->setText(QString::fromStdWString(card.reading));
    else
        ui->hiddenLabel->setText(QString::fromStdWString(card.description));
}

void RepeatWindow::onEasyButtonPressed()
{
    controller->markEasy(card.id, paramType);
    accept();
}

void RepeatWindow::onGoodButtonPressed()
{
    controller->markGood(card.id, paramType);
    accept();
}

void RepeatWindow::onAgainButtonPressed()
{
    controller->markAgain(card.id, paramType);
    accept();
}
