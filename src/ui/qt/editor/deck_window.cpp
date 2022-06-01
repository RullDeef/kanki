#include "tools/logger.hpp"
#include "cardview_widget.hpp"
#include "deck_window.hpp"
#include "card_window.hpp"

DeckWindow::DeckWindow(std::shared_ptr<EditorController> controller, QtEditorView &view)
    : ui(new Ui::DeckWindow), controller(controller), view(view)
{
    ui->setupUi(this);
    setModal(true);

    connect(&view, &QtEditorView::showDeckSignal, this, &DeckWindow::onShowDeck);

    connect(ui->addCardButton, &QPushButton::pressed, this, &DeckWindow::onAddCardButtonPressed);
    connect(ui->editCardButton, &QPushButton::pressed, this, &DeckWindow::onEditCardButtonPressed);
    connect(ui->deleteCardButton, &QPushButton::pressed, this, &DeckWindow::onDeleteCardButtonPressed);
    connect(ui->applyChangesButton, &QPushButton::pressed, this, &DeckWindow::onApplyChangesButtonPressed);
    connect(ui->discardChangesButton, &QPushButton::pressed, this, &DeckWindow::onDiscardButtonPressed);
}

DeckWindow::~DeckWindow()
{
    delete ui;
}

void DeckWindow::onShowDeck(const DeckParams &deck)
{
    LOG_METHOD();

    ui->deckNameEdit->setText(QString::fromStdWString(deck.name));

    ui->cardListWidget->clear();
    for (auto card : deck.cards)
    {
        auto item = new QListWidgetItem(ui->cardListWidget);
        auto cardView = new CardViewWidget(card);
        item->setData(Qt::UserRole, QVariant(QString::fromStdString(uuids::to_string(card.id))));
        item->setSizeHint(cardView->sizeHint());
        ui->cardListWidget->addItem(item);
        ui->cardListWidget->setItemWidget(item, cardView);
    }
}

void DeckWindow::onAddCardButtonPressed()
{
    LOG_METHOD();

    /// KOSTYLI prevents reset of deck name
    controller->setDeckName(ui->deckNameEdit->text().toStdWString());

    auto cardWindow = CardWindow(controller, view);
    controller->addCard();
    cardWindow.exec();
}

void DeckWindow::onEditCardButtonPressed()
{
    LOG_METHOD();

    auto selected = ui->cardListWidget->selectionModel()->selectedIndexes();
    if (selected.empty())
        WARN_METHOD("selected empty");
    else
    {
        /// KOSTYLI prevents reset of deck name
        controller->setDeckName(ui->deckNameEdit->text().toStdWString());

        auto cardId = *UUID::from_string(selected.first().data(Qt::UserRole).toString().toStdString());

        auto cardWindow = CardWindow(controller, view);
        controller->editCard(cardId);
        cardWindow.exec();
    }
}

void DeckWindow::onDeleteCardButtonPressed()
{
    LOG_METHOD();

    auto selected = ui->cardListWidget->selectionModel()->selectedIndexes();
    if (selected.empty())
        WARN_METHOD("nothing selected");
    else
    {
        /// KOSTYLI prevents reset of deck name
        controller->setDeckName(ui->deckNameEdit->text().toStdWString());

        auto cardId = *UUID::from_string(selected.first().data(Qt::UserRole).toString().toStdString());
        controller->removeCard(cardId);
    }
}

void DeckWindow::onApplyChangesButtonPressed()
{
    LOG_METHOD();

    controller->setDeckName(ui->deckNameEdit->text().toStdWString());
    controller->saveActiveDeck();
    accept();
}

void DeckWindow::onDiscardButtonPressed()
{
    LOG_METHOD();

    controller->rejectActiveDeck();
    reject();
}
