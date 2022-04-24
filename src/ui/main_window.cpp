#include <QString>
#include "tools/logger.hpp"
#include "tools/convertor.hpp"
#include "core/controllerprovider.hpp"
#include "deck_window.hpp"
#include "main_window.hpp"

MainWindow::MainWindow(std::shared_ptr<ControllerProvider> controllerProvider)
    : ui(new Ui::MainWindow), controllerProvider(controllerProvider)
{
    ui->setupUi(this);

    connect(&view, &QtCollectionView::showCollectionSignal, this, &MainWindow::onShowCollection);

    connect(ui->addDeckButton, &QPushButton::pressed, this, &MainWindow::onAddDeckButtonPressed);
    connect(ui->editDeckButton, &QPushButton::pressed, this, &MainWindow::onEditDeckButtonPressed);
    connect(ui->learnDeckButton, &QPushButton::pressed, this, &MainWindow::onLearnDeckButtonPressed);
    connect(ui->repeatDeckButton, &QPushButton::pressed, this, &MainWindow::onRepeatDeckButtonPressed);
    connect(ui->deleteDeckButton, &QPushButton::pressed, this, &MainWindow::onDeleteDeckButtonPressed);

    controller = controllerProvider->getCollectionController(&view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onShowCollection(const CollectionParams& collectionParams)
{
    LOG_METHOD();

    ui->decksList->clear();
    for (auto [token, name] : collectionParams.getDeckListInfo())
    {
        auto item = new QListWidgetItem();
        item->setText(QString::fromStdString(name));
        item->setData(Qt::UserRole, QVariant(QString::fromStdString(token)));
        ui->decksList->addItem(item);
    }
}

void MainWindow::onAddDeckButtonPressed()
{
    LOG_METHOD();

    auto deckToken = controller->addDeck();

    auto deckWindow = DeckWindow(controllerProvider, deckToken);
    deckWindow.exec();
}

void MainWindow::onEditDeckButtonPressed()
{
    LOG_METHOD();

    auto selected = ui->decksList->selectionModel()->selectedIndexes();
    if (selected.empty())
        WARN_METHOD("selected empty");
    else
    {
        auto deckToken = selected.first().data(Qt::UserRole).toString().toStdString();
        ///TODO: controller->editDeck(deckIndex);

        auto deckWindow = DeckWindow(controllerProvider, deckToken);
        deckWindow.exec();
    }
}

void MainWindow::onLearnDeckButtonPressed()
{
    LOG_METHOD();

    auto selected = ui->decksList->selectedItems();
    if (selected.empty())
        WARN_METHOD("selected empty");
    else
    {
        auto selectedDeckName = selected.front()->text().toStdString();

        // auto subview = std::unique_ptr<QtActivityView>(new QtDeckView);
        // auto subcontroller = controller->editDeck(subview.get(), selectedDeckName);

        // auto deckWindow = DeckWindow(subview.get(), subcontroller);

        // subcontroller->initialize(DeckParams());
        // deckWindow.exec();
        ERROR_METHOD("implement");
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
        auto deckToken = selected.first().data(Qt::UserRole).toString().toStdString();

        // auto subview = std::unique_ptr<QtActivityView>(new QtDeckView);
        // auto subcontroller = controller->editDeck(subview.get(), selectedDeckName);

        // auto deckWindow = DeckWindow(subview.get(), subcontroller);

        // subcontroller->initialize(DeckParams());
        // deckWindow.exec();
        ERROR_METHOD("implement");
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
        auto deckToken = selected.first().data(Qt::UserRole).toString().toStdString();
        controller->deleteDeck(deckToken);
    }
}
