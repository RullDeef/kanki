#include <QString>
#include <QFileDialog>
#include "tools/logger.hpp"
#include "editor/deck_window.hpp"
#include "learn/learn_window.hpp"
#include "learn/info_window.hpp"
#include "main_window.hpp"

MainWindow::MainWindow(
    std::shared_ptr<EditorController> editorController,
    std::shared_ptr<LearnerController> learnerController,
    std::shared_ptr<IOController> ioController)
    : ui(new Ui::MainWindow),
      editorController(editorController),
      learnerController(learnerController),
      ioController(ioController)
{
    ui->setupUi(this);

    connect(ui->addDeckButton, &QPushButton::pressed, this, &MainWindow::onAddDeckButtonPressed);
    connect(ui->editDeckButton, &QPushButton::pressed, this, &MainWindow::onEditDeckButtonPressed);
    connect(ui->learnDeckButton, &QPushButton::pressed, this, &MainWindow::onLearnDeckButtonPressed);
    connect(ui->repeatDeckButton, &QPushButton::pressed, this, &MainWindow::onRepeatDeckButtonPressed);
    connect(ui->deleteDeckButton, &QPushButton::pressed, this, &MainWindow::onDeleteDeckButtonPressed);

    connect(ui->importAction, &QAction::triggered, this, &MainWindow::onImportAction);
    connect(ui->exportAction, &QAction::triggered, this, &MainWindow::onExportAction);

    editorViewAdapter = new EditorViewAdapter(editorView);
    editorController->setView(editorViewAdapter);
    connect(&editorView, &QtEditorView::showCollectionSignal, this, &MainWindow::onShowCollection);

    learnerViewAdapter = new LearnerViewAdapter(learnerView);
    learnerController->setView(learnerViewAdapter);
    learnerView.setController(learnerController);

    ioViewAdapter = new IOViewAdapter(ioView);
    ioController->setView(ioViewAdapter);
    ioView.setEditorController(editorController);

    /// KOSTYLI show starting collection to work with
    editorController->editCollection();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete editorViewAdapter;
    delete learnerViewAdapter;
}

void MainWindow::onShowCollection(const CollectionParams &collection)
{
    LOG_METHOD();

    ui->decksList->clear();
    for (auto deck : collection.decks)
    {
        auto id = uuids::to_string(deck.id);
        auto name = deck.name;

        auto item = new QListWidgetItem();
        item->setText(QString::fromStdWString(name));
        item->setData(Qt::UserRole, QVariant(QString::fromStdString(id)));

        ui->decksList->addItem(item);
    }
}

void MainWindow::onAddDeckButtonPressed()
{
    LOG_METHOD();

    auto deckWindow = DeckWindow(editorController, editorView);
    editorController->addDeck();
    deckWindow.exec();

    editorController->saveActiveCollection();
}

void MainWindow::onEditDeckButtonPressed()
{
    LOG_METHOD();

    auto selected = ui->decksList->selectionModel()->selectedIndexes();
    if (selected.empty())
        WARN_METHOD("selected empty");
    else
    {
        auto deckId = *UUID::from_string(selected.first().data(Qt::UserRole).toString().toStdString());

        auto deckWindow = DeckWindow(editorController, editorView);
        editorController->editDeck(deckId);
        deckWindow.exec();

        editorController->saveActiveCollection();
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
        auto deckId = *UUID::from_string(selected.first().data(Qt::UserRole).toString().toStdString());

        editorController->removeDeck(deckId);
        editorController->saveActiveCollection();
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
        auto deckId = *UUID::from_string(selected.first().data(Qt::UserRole).toString().toStdString());

        learnerController->learnNext(deckId);
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
        auto deckId = *UUID::from_string(selected.first().data(Qt::UserRole).toString().toStdString());

        learnerController->repeatNext(deckId);
    }
}

void MainWindow::onImportAction()
{
    auto filename = QFileDialog::getOpenFileName(this,
        tr("Import collection"), NULL, tr("Text Files (*.txt)")).toStdString();

    if (!filename.empty())
        ioController->importCollection(filename);
}

void MainWindow::onExportAction()
{
    auto filename = QFileDialog::getSaveFileName(this,
        tr("Import collection"), NULL, tr("Text Files (*.txt)")).toStdString();

    if (!filename.empty())
        ioController->exportCollection(filename);
}
