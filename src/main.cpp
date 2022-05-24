#include <memory>
#include <QApplication>

#include "core/editorcontroller.hpp"
#include "db/filecollectionrepo.hpp"
#include "ui/main_window.hpp"

constexpr auto collectionFilename = "collection.txt";
constexpr auto sessionsFilename = "sessions.txt";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::unique_ptr<ICollectionRepository> collectionRepo(
        new FileCollectionRepository(collectionFilename));

    EditorController editorController(collectionRepo.get());

    auto mainWindow = MainWindow(editorController);
    mainWindow.show();

    return app.exec();
}
