#include <iostream>
#include "application.hpp"
#include "menu.hpp"

cli::Application::Application()
{
    editorViewAdapter = new EditorViewAdapter(editorView);
}

cli::Application::~Application()
{
    delete editorViewAdapter;
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
}

int cli::Application::run()
{
    cli::Menu mainMenu("=== Главное меню ===");

    mainMenu.addOption("Редактировать коллекцию", [this]() {
        editorController->editCollection();
    });

    mainMenu.run(true);
    return 0;
}
