#include <iostream>
#include <memory>
#include <QWidget>
#include <QApplication>
#include "core/collectioncontroller.hpp"
#include "db/filerepofactory.hpp"
#include "ui/main_window.hpp"

constexpr auto collectionFilename = "collection.txt";
constexpr auto sessionsFilename = "sessions.txt";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto repoFactory = std::shared_ptr<IRepositoryFactory>(new FileRepositoryFactory(collectionFilename, sessionsFilename));
    auto controllerProvider = std::make_shared<ControllerProvider>(repoFactory);

    auto mainWindow = MainWindow(controllerProvider);
    mainWindow.show();

    return app.exec();
}
