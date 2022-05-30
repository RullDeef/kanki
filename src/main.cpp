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
#include "db/fileexporter.hpp"
#include "db/fileimporter.hpp"

#define UI_CLI true

#if UI_CLI
    #include "cli/application.hpp"
#else
    #include <QApplication>
    #include "ui/main_window.hpp"
#endif

constexpr auto collectionFilename = "collection.txt";
constexpr auto sessionsFilename = "sessions.txt";

int ui_solution(int argc, char *argv[],
                EditorController &editorController,
                LearnerController &learnerController,
                IOController &ioController)
{
#if UI_CLI
    cli::Application app;
    app.setEditorController(editorController);
    app.setLearnerController(learnerController);
    app.setIOController(ioController);
    return app.run();
#else
    QApplication app(argc, argv);
    auto mainWindow = MainWindow(editorController, learnerController);
    mainWindow.show();
    return app.exec();
#endif
}

int main(int argc, char *argv[])
{
    FileDTOIOFactory collectionIOFactory(collectionFilename);
    FileDTOIOFactory sessionIOFactory(sessionsFilename);

    FileImporter importer;
    FileExporter exporter;

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

        IOController ioController(&collectionManager, &sessionManager);

        ioController.setImporter(&importer);
        ioController.setExporter(&exporter);

        res = ui_solution(argc, argv, editorController, learnerController, ioController);
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
