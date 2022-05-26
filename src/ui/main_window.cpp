#include <QString>
#include "tools/logger.hpp"
#include "ui/editor/deck_window.hpp"
#include "ui/learn/learn_window.hpp"
#include "ui/learn/info_window.hpp"
#include "ui/main_window.hpp"

MainWindow::MainWindow(EditorController &editorController, LearnerController &learnerController)
    : ui(new Ui::MainWindow), editorController(editorController), learnerController(learnerController)
{
    ui->setupUi(this);

    connect(ui->addDeckButton, &QPushButton::pressed, this, &MainWindow::onAddDeckButtonPressed);
    connect(ui->editDeckButton, &QPushButton::pressed, this, &MainWindow::onEditDeckButtonPressed);
    connect(ui->learnDeckButton, &QPushButton::pressed, this, &MainWindow::onLearnDeckButtonPressed);
    connect(ui->repeatDeckButton, &QPushButton::pressed, this, &MainWindow::onRepeatDeckButtonPressed);
    connect(ui->deleteDeckButton, &QPushButton::pressed, this, &MainWindow::onDeleteDeckButtonPressed);

    editorController.setView(&editorView);
    connect(&editorView, &QtEditorView::showCollectionSignal, this, &MainWindow::onShowCollection);

    learnerController.setView(&learnerView);
    learnerView.setController(&learnerController);

    /// KOSTYLI show starting collection to work with
    editorController.editCollection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onShowCollection(const Collection &collection)
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

    auto deckWindow = DeckWindow(editorController, editorView);
    editorController.addDeck();
    deckWindow.exec();

    editorController.saveActiveCollection();
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

        auto deckWindow = DeckWindow(editorController, editorView);
        editorController.editDeck(deckId);
        deckWindow.exec();

        editorController.saveActiveCollection();
    }
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

        editorController.removeDeck(deckId);
        editorController.saveActiveCollection();
    }
}

void MainWindow::onLearnDeckButtonPressed()
{
    LOG_METHOD();

    auto selected = ui->decksList->selectionModel()->selectedIndexes();
    if (selected.empty())
        WARN_METHOD("selected empty");
    else
    {
        size_t deckId = selected.first().data(Qt::UserRole).toULongLong();
        learnerController.learnNext(deckId);
    }
}

void MainWindow::onRepeatDeckButtonPressed()
{
    LOG_METHOD();

    auto selected = ui->decksList->selectionModel()->selectedIndexes();
    if (selected.empty())
        WARN_METHOD("selected empty");
    else
    {
        size_t deckId = selected.first().data(Qt::UserRole).toULongLong();
        learnerController.repeatNext(deckId);
    }
}
