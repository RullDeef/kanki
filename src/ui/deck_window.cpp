#include "tools/logger.hpp"
#include "cardview_widget.hpp"
#include "deck_window.hpp"

DeckWindow::DeckWindow(std::shared_ptr<ControllerProvider> controllerProvider, const std::string& deckToken)
    : ui(new Ui::DeckWindow), controllerProvider(controllerProvider), deckToken(deckToken)
{
    ui->setupUi(this);
    setModal(true);

    connect(&view, &QtDeckView::onShowDeck, this, &DeckWindow::onShowDeck);

    connect(ui->addCardButton, &QPushButton::pressed, this, &DeckWindow::onAddCardButtonPressed);
    connect(ui->editCardButton, &QPushButton::pressed, this, &DeckWindow::onEditCardButtonPressed);
    connect(ui->deleteCardButton, &QPushButton::pressed, this, &DeckWindow::onDeleteCardButtonPressed);
    connect(ui->applyChangesButton, &QPushButton::pressed, this, &DeckWindow::onApplyChangesButtonPressed);
    connect(ui->discardChangesButton, &QPushButton::pressed, this, &DeckWindow::onDiscardButtonPressed);

    controller = controllerProvider->getDeckController(&view, deckToken);
}

DeckWindow::~DeckWindow()
{
    delete ui;
}

void DeckWindow::onShowDeck(const DeckParams& deckParams)
{
    LOG_METHOD();

    ui->deckNameEdit->setText(QString::fromStdString(deckParams.getName()));

    ui->cardListWidget->clear();
    for (const auto& cardParams : deckParams)
    {
        auto item = new QListWidgetItem(ui->cardListWidget);
        auto cardView = new CardViewWidget(cardParams.second);
        item->setData(Qt::UserRole, QString::fromStdString(cardParams.first));
        item->setSizeHint(cardView->sizeHint());
        ui->cardListWidget->addItem(item);
        ui->cardListWidget->setItemWidget(item, cardView);
    }
}


void DeckWindow::onAddCardButtonPressed()
{
    WARN_METHOD("implement");
}

void DeckWindow::onEditCardButtonPressed()
{
    WARN_METHOD("implement");
}

void DeckWindow::onDeleteCardButtonPressed()
{
    LOG_METHOD();

    auto selected = ui->cardListWidget->selectionModel()->selectedIndexes();
    if (selected.empty())
        WARN_METHOD("nothing selected");
    else
    {
        auto cardToken = selected.first().data(Qt::UserRole).toString().toStdString();
        controller->deleteCard(cardToken);
    }
}

void DeckWindow::onApplyChangesButtonPressed()
{
    LOG_METHOD();

    controller->setDeckName(ui->deckNameEdit->text().toStdString());    
    controller->apply();
    accept();
}

void DeckWindow::onDiscardButtonPressed()
{
    LOG_METHOD();

    controller->discard();
    reject();
}

