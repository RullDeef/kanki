#include <iostream>
#include "tools/convertor.hpp"
#include "cli/menu.hpp"
#include "editorview.hpp"

void cli::EditorView::setEditorController(EditorController &newController)
{
    controller = &newController;
}

void cli::EditorView::showCollection(const CollectionParams &collection)
{
    cli::Menu menu("=== Редактирование коллекции ===");

    std::cout << "Коллекция:\n";
    for (auto deck : collection.decks)
        std::cout << deck.id << ": " << Convert::toString(deck.name) << std::endl;

    auto getDeckIdFunc = []() -> size_t
    {
        size_t deckId;
        std::cout << "Введите идентификатор колоды: ";
        std::cin >> deckId;
        return deckId;
    };

    menu.addOption("Добавить колоду", [this]()
                   { controller->addDeck(); });

    menu.addOption("Изменить колоду", [this, getDeckIdFunc]()
                   {
        auto deckId = getDeckIdFunc();
        controller->editDeck(deckId); });

    menu.addOption("Удалить колоду", [this, getDeckIdFunc]()
                   {
        auto deckId = getDeckIdFunc();
        controller->removeDeck(deckId); });

    menu.addOption("Сохранить изменения", [this]()
                   { controller->saveActiveCollection(); });
    menu.addOption("Отменить изменения", [this]()
                   { controller->rejectActiveCollection(); });

    menu.run();
}

void cli::EditorView::showDeck(const DeckParams &deck)
{
    cli::Menu menu("=== Редактирование колоды ===");

    std::cout << "Колода '" << Convert::toString(deck.name) << "'\n";
    for (auto card : deck.cards)
        std::cout << card.id << ": "
                  << Convert::toString(card.symbol) << " - "
                  << Convert::toString(card.reading) << std::endl;

    auto getCardIdFunc = []() -> size_t
    {
        size_t cardId;
        std::cout << "Введите идентификатор карточки: ";
        std::cin >> cardId;
        return cardId;
    };

    menu.addOption("Добавить карточку", [this]()
                   { controller->addCard(); });

    menu.addOption("Изменить карточку", [this, getCardIdFunc]()
                   {
        auto cardId = getCardIdFunc();
        controller->editCard(cardId); });

    menu.addOption("Удалить карточку", [this, getCardIdFunc]()
                   {
        auto cardId = getCardIdFunc();
        controller->removeCard(cardId); });

    menu.addOption("Сохранить изменения", [this]()
                   { controller->saveActiveDeck(); });
    menu.addOption("Отменить изменения", [this]()
                   { controller->rejectActiveDeck(); });

    menu.run();
}

void cli::EditorView::showCard(const CardParams &card)
{
    cli::Menu menu("=== Редактирование карточки ===");

    std::cout << "card #" << card.id << std::endl;
    std::cout << "symbol: " << Convert::toString(card.symbol) << std::endl;
    std::cout << "reading: " << Convert::toString(card.reading) << std::endl;
    std::cout << "description: " << Convert::toString(card.description) << std::endl;

    menu.addOption("Изменить символ", [this]()
                   {
        std::string value;
        std::cout << "Введите новый символ: ";
        std::getline(std::cin, value);

        controller->setCardSymbol(Convert::toWString(value)); });

    menu.addOption("Изменить чтение", [this]()
                   {
        std::string value;
        std::cout << "Введите новое чтение: ";
        std::getline(std::cin, value);

        controller->setCardReading(Convert::toWString(value)); });

    menu.addOption("Изменить перевод", [this]()
                   {
        std::string value;
        std::cout << "Введите новый перевод: ";
        std::getline(std::cin, value);

        controller->setCardDescription(Convert::toWString(value)); });

    menu.addOption("Сохранить изменения", [this]()
                   { controller->saveActiveCard(); });
    menu.addOption("Отменить изменения", [this]()
                   { controller->rejectActiveCard(); });

    menu.run();
}
