#include <QString>
#include "tools/logger.hpp"
#include "deck_window.hpp"
#include "main_window.hpp"

MainWindow::MainWindow(EditorController& controller)
    : ui(new Ui::MainWindow), controller(controller)
{
    ui->setupUi(this);

    connect(ui->addDeckButton, &QPushButton::pressed, this, &MainWindow::onAddDeckButtonPressed);
    connect(ui->editDeckButton, &QPushButton::pressed, this, &MainWindow::onEditDeckButtonPressed);
    connect(ui->learnDeckButton, &QPushButton::pressed, this, &MainWindow::onLearnDeckButtonPressed);
    connect(ui->repeatDeckButton, &QPushButton::pressed, this, &MainWindow::onRepeatDeckButtonPressed);
    connect(ui->deleteDeckButton, &QPushButton::pressed, this, &MainWindow::onDeleteDeckButtonPressed);

    controller.setView(&view);
    connect(&view, &QtEditorView::showCollectionSignal, this, &MainWindow::onShowCollection);

    controller.editCollection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onShowCollection(const Collection& collection)
{
    LOG_METHOD();

    ui->decksList->clear();
    for (auto deck : collection)
    {
        auto id = deck.getId();
        auto name = deck.getName();

        auto item = new QListWidgetItem();
        item->setText(QString::fromStdWString(name));
        item->setData(Qt::UserRole, QVariant(qlonglong(id)));

        ui->decksList->addItem(item);
    }
}

void MainWindow::onAddDeckButtonPressed()
{
    LOG_METHOD();

    auto deckWindow = DeckWindow(controller, view);
    controller.addDeck();
    deckWindow.exec();

    controller.saveActiveCollection();
}

void MainWindow::onEditDeckButtonPressed()
{
    LOG_METHOD();

    auto selected = ui->decksList->selectionModel()->selectedIndexes();
    if (selected.empty())
        WARN_METHOD("selected empty");
    else
    {
        size_t deckId = selected.first().data(Qt::UserRole).toULongLong();

        auto deckWindow = DeckWindow(controller, view);
        controller.editDeck(deckId);
        deckWindow.exec();
        
        controller.saveActiveCollection();
    }
}

void MainWindow::onLearnDeckButtonPressed()
{
    WARN_METHOD();

    // auto selected = ui->decksList->selectedItems();
    // if (selected.empty())
    //     WARN_METHOD("selected empty");
    // else
    // {
    //     size_t deckId = selected.front()->text().toULongLong();
    //     controller->learnDeck(deckId);
    // }
}

void MainWindow::onRepeatDeckButtonPressed()
{
    WARN_METHOD();

    // auto selected = ui->decksList->selectionModel()->selectedIndexes();
    // if (selected.empty())
    //     WARN_METHOD("selected empty");
    // else
    // {
    //     size_t deckId = selected.first().data(Qt::UserRole).toULongLong();
    //     controller->repeatDeck(deckId);
    // }
}

void MainWindow::onDeleteDeckButtonPressed()
{
    LOG_METHOD();

    auto selected = ui->decksList->selectionModel()->selectedIndexes();
    if (selected.empty())
        WARN_METHOD("selected empty");
    else
    {
        size_t deckId = selected.first().data(Qt::UserRole).toULongLong();
        
        controller.removeDeck(deckId);
        controller.saveActiveCollection();
    }
}
