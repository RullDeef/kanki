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
    updateDeckIdMapping(collection);

    cli::Menu menu("=== Редактирование коллекции ===");

    std::cout << "Коллекция:\n";
    for (size_t index = 1; auto deck : collection.decks)
        std::cout << index++ << ": "
                  << Convert::toString(deck.name) << std::endl;

    auto getDeckIdFunc = [this]() -> UUID
    {
        size_t deckId;
        std::cout << "Введите номер колоды: ";
        std::cin >> deckId;
        return deckIdMapping[deckId];
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
    updateCardIdMapping(deck);

    cli::Menu menu("=== Редактирование колоды ===");

    std::cout << "Колода '" << Convert::toString(deck.name) << "'\n";
    for (size_t index = 1; auto card : deck.cards)
        std::cout << index++ << ": "
                  << Convert::toString(card.symbol) << " - "
                  << Convert::toString(card.reading) << std::endl;

    auto getCardIdFunc = [this]() -> UUID
    {
        size_t cardId;
        std::cout << "Введите номер карточки: ";
        std::cin >> cardId;
        return cardIdMapping[cardId];
    };

    menu.addOption("Добавить карточку", [this]()
                   { controller->addCard(); });

    menu.addOption("Изменить карточку", [this, getCardIdFunc]()
                   { controller->editCard(getCardIdFunc()); });

    menu.addOption("Удалить карточку", [this, getCardIdFunc]()
                   { controller->removeCard(getCardIdFunc()); });
    
    menu.addOption("Изменить название колоды", [this]() {
        std::string name;
        std::cout << "Введите новое название: ";
        std::getline(std::cin, name);
        controller->setDeckName(Convert::toWString(name));
    });

    menu.addOption("Сохранить изменения", [this]()
                   { controller->saveActiveDeck(); });
    menu.addOption("Отменить изменения", [this]()
                   { controller->rejectActiveDeck(); });

    menu.run();
}

void cli::EditorView::showCard(const CardParams &card)
{
    cli::Menu menu("=== Редактирование карточки ===");

    std::cout << "card id: " << card.id << std::endl;
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

const std::map<size_t, UUID> &cli::EditorView::getDeckIdMapping() const
{
    return deckIdMapping;
}

void cli::EditorView::updateDeckIdMapping(const CollectionParams &collection)
{
    deckIdMapping.clear();

    for (size_t index = 1; auto deck : collection.decks)
        deckIdMapping[index++] = deck.id;
}

void cli::EditorView::updateCardIdMapping(const DeckParams &deck)
{
    cardIdMapping.clear();

    for (size_t index = 1; auto card : deck.cards)
        cardIdMapping[index++] = card.id;
}
