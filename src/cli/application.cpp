#include <iostream>
#include "application.hpp"
#include "menu.hpp"

cli::Application::Application()
{
    editorViewAdapter = new EditorViewAdapter(editorView);
    learnerViewAdapter = new LearnerViewAdapter(learnerView);
}

cli::Application::~Application()
{
    delete editorViewAdapter;
    delete learnerViewAdapter;
}

void cli::Application::setEditorController(EditorController &controller)
{
    editorController = &controller;
    controller.setView(editorViewAdapter);

    editorView.setEditorController(controller);
}

void cli::Application::setLearnerController(LearnerController &controller)
{
    learnerController = &controller;
    controller.setView(learnerViewAdapter);

    learnerView.setLearnerController(controller);
}

int cli::Application::run()
{
    cli::Menu mainMenu("=== Главное меню ===");

    auto getDeckIdFunc = []() -> size_t
    {
        size_t deckId;
        std::cout << "Введите идентификатор колоды: ";
        std::cin >> deckId;
        return deckId;
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

    mainMenu.run(true);
    return 0;
}
