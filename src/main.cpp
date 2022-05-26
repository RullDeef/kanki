#include <QApplication>
#include "core/collectionmanager.hpp"
#include "core/sessionmanager.hpp"
#include "core/editorcontroller.hpp"
#include "core/learnercontroller.hpp"
#include "core/spacedlearner.hpp"
#include "core/spacedestimator.hpp"
#include "db/filecollectionrepo.hpp"
#include "db/filesessionrepo.hpp"
#include "ui/main_window.hpp"

constexpr auto collectionFilename = "collection.txt";
constexpr auto sessionsFilename = "sessions.txt";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ICollectionRepository* collectionRepo = new FileCollectionRepository(collectionFilename);
    ISessionRepository* sessionRepo = new FileSessionRepository(sessionsFilename);

    int res;
    {
        CollectionManager collectionManager(collectionRepo);
        SessionManager sessionManager(sessionRepo);

        EditorController editorController(&collectionManager);

        SpacedLearner spacedLearner(&collectionManager, &sessionManager);
        SpacedEstimator spacedEstimator;

        LearnerController learnerController(&collectionManager, &sessionManager);

        learnerController.setLearner(&spacedLearner);
        learnerController.setEstimator(&spacedEstimator);

        auto mainWindow = MainWindow(editorController, learnerController);
        mainWindow.show();

        res = app.exec();
    }

    delete collectionRepo;
    delete sessionRepo;

    return res;
}
