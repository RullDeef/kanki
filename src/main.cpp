#include <QApplication>
#include "tools/logger.hpp"
#include "core/collectionmanager.hpp"
#include "core/sessionmanager.hpp"
#include "core/editorcontroller.hpp"
#include "core/learnercontroller.hpp"
#include "core/spacedlearner.hpp"
#include "core/spacedestimator.hpp"
#include "db/filedtoiofactory.hpp"
#include "db/filecollectionrepo.hpp"
#include "db/filesessionrepo.hpp"
#include "ui/main_window.hpp"

constexpr auto collectionFilename = "collection.txt";
constexpr auto sessionsFilename = "sessions.txt";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FileDTOIOFactory collectionIOFactory(collectionFilename);
    FileDTOIOFactory sessionIOFactory(sessionsFilename);

    auto collectionRepo = new FileCollectionRepository();
    auto sessionRepo = new FileSessionRepository();

    TRY_FUNC(
        auto reader = collectionIOFactory.createReader();
        collectionRepo->load(*reader.get()));

    TRY_FUNC(
        auto reader = sessionIOFactory.createReader();
        sessionRepo->load(*reader.get()));

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

    TRY_FUNC(
        auto writer = collectionIOFactory.createWriter();
        collectionRepo->dump(*writer.get()));

    TRY_FUNC(
        auto writer = sessionIOFactory.createWriter();
        sessionRepo->dump(*writer.get()));

    delete collectionRepo;
    delete sessionRepo;

    return res;
}
