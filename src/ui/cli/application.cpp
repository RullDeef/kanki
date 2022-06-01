#include <iostream>
#include "application.hpp"
#include "menu.hpp"

cli::Application::Application()
{
    editorViewAdapter = new EditorViewAdapter(editorView);
    learnerViewAdapter = new LearnerViewAdapter(learnerView);
    ioViewAdapter = new IOViewAdapter(ioView);
}

cli::Application::~Application()
{
    delete editorViewAdapter;
    delete learnerViewAdapter;
    delete ioViewAdapter;
}

void cli::Application::setEditorController(std::shared_ptr<EditorController> controller)
{
    editorController = controller;
    controller->setView(editorViewAdapter);

    editorView.setEditorController(controller);
}

void cli::Application::setLearnerController(std::shared_ptr<LearnerController> controller)
{
    learnerController = controller;
    controller->setView(learnerViewAdapter);

    learnerView.setLearnerController(controller);
}

void cli::Application::setIOController(std::shared_ptr<IOController> controller)
{
    ioController = controller;
    controller->setView(ioViewAdapter);
}

int cli::Application::run()
{
    cli::Menu mainMenu("=== Главное меню ===");

    auto editorViewPtr = &editorView;

    auto getDeckIdFunc = [editorViewPtr]() -> UUID
    {
        size_t deckId;
        std::cout << "Введите номер колоды: ";
        std::cin >> deckId;
        return editorViewPtr->getDeckIdMapping().at(deckId);
    };

    auto getFilenameFucn = []() -> std::string
    {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::getline(std::cin, filename);
        return filename;
    };

    mainMenu.addOption("Редактировать коллекцию", [this]() {
        editorController->editCollection();
    });

    mainMenu.addOption("Изучить карточки из колоды", [this, getDeckIdFunc]() {
        learnerController->learnNext(getDeckIdFunc());
    });

    mainMenu.addOption("Повторить карточки из колоды", [this, getDeckIdFunc]() {
        learnerController->repeatNext(getDeckIdFunc());
    });

    mainMenu.addOption("Экспортировать коллекцию", [this, getFilenameFucn]() {
        ioController->exportCollection(getFilenameFucn());
    });

    mainMenu.addOption("Импортировать коллекцию", [this, getFilenameFucn]() {
        ioController->importCollection(getFilenameFucn());
    });

    mainMenu.run(true);
    return 0;
}
