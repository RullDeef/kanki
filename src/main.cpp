#include "core/collectionmanager.hpp"
#include "core/sessionmanager.hpp"
#include "solution/cfgsolution.hpp"

int main(int argc, char *argv[])
{
    ConfigFileSolution solution("./assets/kanki.cfg");

    auto collectionManager = std::shared_ptr<ICollectionManager>(
        new CollectionManager(solution.getCollectionRepository()));
    auto sessionManager = std::shared_ptr<ISessionManager>(
        new SessionManager(solution.getSessionRepository()));

    auto editorController = std::make_shared<EditorController>(collectionManager);
    auto learnerController = std::make_shared<LearnerController>(collectionManager, sessionManager);
    auto ioController = std::make_shared<IOController>(collectionManager, sessionManager);

    learnerController->setLearner(solution.getLearner());
    learnerController->setEstimator(solution.getEstimator());

    ioController->setImporter(solution.getImporter());
    ioController->setExporter(solution.getExporter());

    auto uiFactory = solution.getUIFactory();

    uiFactory->setEditorController(editorController);
    uiFactory->setLearnerController(learnerController);
    uiFactory->setIOController(ioController);

    return uiFactory->runApplication(argc, argv);
}
