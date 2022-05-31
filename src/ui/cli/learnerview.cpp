#include <iostream>
#include <stdexcept>
#include "tools/convertor.hpp"
#include "learnerview.hpp"
#include "menu.hpp"

void cli::LearnerView::setLearnerController(std::shared_ptr<LearnerController> newController)
{
    controller = newController;
}

void cli::LearnerView::showCard(const CardParams &params)
{
    cli::Menu menu("=== Подтверждение изучения ===");

    std::cout << "Новая карточка:\n";

    std::cout << "символ: " << Convert::toString(params.symbol) << std::endl;
    std::cout << "чтение: " << Convert::toString(params.reading) << std::endl;
    std::cout << "перевод: " << Convert::toString(params.description) << std::endl;

    menu.addOption("ок", [this, &menu, params]()
                   {
        controller->confirmLearned(params.id);
        menu.exit(); });

    menu.run(true);
}

void cli::LearnerView::askCard(const CardParams &card, int paramType)
{
    std::cout << "[<< Карточка >>]\n";

    std::cout << "символ: " << Convert::toString(card.symbol) << std::endl;
    if (paramType == Snapshot::ParamType::READING)
    {
        std::cout << "перевод: " << Convert::toString(card.description) << std::endl;
        std::cout << "Вспомните чтение.\n";
    }
    else
    {
        std::cout << "чтение: " << Convert::toString(card.reading) << std::endl;
        std::cout << "Вспомните перевод.\n";
    }

    cli::Menu menu;
    menu.addOption("показать...", [this, card, paramType]()
                   {
        if (paramType == Snapshot::ParamType::READING)
            std::cout << "чтение: " << Convert::toString(card.reading) << std::endl;
        else
            std::cout << "перевод: " << Convert::toString(card.description) << std::endl;
        
        cli::Menu menu("Оцените собственные знания:");

        menu.addOption("Легко", [this, card, paramType]() {
            controller->markEasy(card.id, paramType);
        });

        menu.addOption("Трудно", [this, card, paramType]() {
            controller->markGood(card.id, paramType);
        });

        menu.addOption("Не помню", [this, card, paramType]() {
            controller->markAgain(card.id, paramType);
        });

        menu.run(); });
    menu.run();
}

void cli::LearnerView::noCardsForLearn()
{
    std::cout << "К сожалению, нет новых карточек для запоминания\n";
}

void cli::LearnerView::noCardsForRepeat()
{
    std::cout << "К сожалению, нет новых карточек для повторения\n";
}
