#include <algorithm>
#include "tools/logger.hpp"
#include "tools/convertor.hpp"
#include "editorcontroller.hpp"

EditorController::EditorController(std::shared_ptr<ICollectionManager> collectionManager)
    : collectionManager(collectionManager)
{
}

EditorController::~EditorController()
{
    delete activeCollection;
    delete activeDeck;
    delete activeCard;
}

void EditorController::setView(IEditorView *newView)
{
    view = newView;
}

void EditorController::addCollection()
{
    LOG_METHOD();

    delete activeCollection;
    activeCollection = new DeckCollection(idGenerator(), L"new collection"); // TODO: collection builder

    if (view != nullptr)
        view->showCollection(*activeCollection);
}

void EditorController::editCollection()
{
    LOG_METHOD("editing active collection");

    delete activeCollection;
    activeCollection = new DeckCollection(collectionManager->getActiveCollection());

    if (view != nullptr)
        view->showCollection(*activeCollection);
}

void EditorController::editCollection(UUID id)
{
    LOG_METHOD("id=" + uuids::to_string(id));

    delete activeCollection;
    activeCollection = new DeckCollection(collectionManager->getCollectionById(id));

    if (view != nullptr)
        view->showCollection(*activeCollection);
}

void EditorController::saveActiveCollection()
{
    LOG_METHOD();

    collectionManager->saveCollection(*activeCollection);
}

void EditorController::rejectActiveCollection()
{
    LOG_METHOD();

    delete activeCollection;
    activeCollection = nullptr;
}

void EditorController::addDeck()
{
    LOG_METHOD();

    delete activeDeck;
    activeDeck = new Deck(idGenerator(), L"new deck"); // TODO: deck builder

    if (view != nullptr)
        view->showDeck(*activeDeck);
}

void EditorController::editDeck(UUID deckId)
{
    LOG_METHOD("id=" + uuids::to_string(deckId));

    try
    {
        auto deck = activeCollection->getDeckById(deckId);

        delete activeDeck;
        activeDeck = new Deck(*deck);

        if (view != nullptr)
            view->showDeck(*activeDeck);
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD("invalid deck id");
    }
}

void EditorController::addCard()
{
    LOG_METHOD();

    delete activeCard;
    activeCard = new Card(idGenerator(), L"symbol", L"reading", L"description"); // TODO: add card builder

    if (view != nullptr)
        view->showCard(*activeCard);
}

void EditorController::editCard(UUID cardId)
{
    LOG_METHOD("id=" + uuids::to_string(cardId));

    try
    {
        auto card = activeDeck->getCardById(cardId);
        delete activeCard;
        activeCard = new Card(*card);

        if (view != nullptr)
            view->showCard(*activeCard);
    }
    catch (const std::exception &e)
    {
        ERROR_METHOD("invalid card id");
    }
}

void EditorController::saveActiveDeck()
{
    LOG_METHOD();

    activeCollection->addDeck(*activeDeck);
    delete activeDeck;
    activeDeck = nullptr;

    if (view != nullptr)
        view->showCollection(*activeCollection);
}

void EditorController::rejectActiveDeck()
{
    LOG_METHOD();

    delete activeDeck;
    activeDeck = nullptr;

    if (view != nullptr)
        view->showCollection(*activeCollection);
}

void EditorController::removeDeck(UUID deckId)
{
    LOG_METHOD("id=" + uuids::to_string(deckId));

    activeCollection->removeDeckById(deckId);

    if (view != nullptr)
        view->showCollection(*activeCollection);
}

void EditorController::removeCard(UUID cardId)
{
    LOG_METHOD("id=" + uuids::to_string(cardId));

    activeDeck->removeCardById(cardId);

    if (view != nullptr)
        view->showDeck(*activeDeck);
}

void EditorController::setDeckName(const std::wstring &newName)
{
    LOG_METHOD("newName=" + Convert::toString(newName));

    if (activeDeck != nullptr)
    {
        activeDeck->setName(newName);

        if (view != nullptr)
            view->showDeck(*activeDeck);
    }
}

void EditorController::setCardSymbol(const std::wstring &value)
{
    LOG_METHOD("value=" + Convert::toString(value));

    if (activeCard != nullptr)
    {
        activeCard->setSymbol(value);

        if (view != nullptr)
            view->showCard(*activeCard);
    }
}

void EditorController::setCardReading(const std::wstring &value)
{
    LOG_METHOD("value=" + Convert::toString(value));

    if (activeCard != nullptr)
    {
        activeCard->setReading(value);

        if (view != nullptr)
            view->showCard(*activeCard);
    }
}

void EditorController::setCardDescription(const std::wstring &value)
{
    LOG_METHOD("value=" + Convert::toString(value));

    if (activeCard != nullptr)
    {
        activeCard->setDescription(value);

        if (view != nullptr)
            view->showCard(*activeCard);
    }
}

void EditorController::saveActiveCard()
{
    LOG_METHOD();

    activeDeck->addCard(*activeCard);

    delete activeCard;
    activeCard = nullptr;

    if (view != nullptr)
        view->showDeck(*activeDeck);
}

void EditorController::rejectActiveCard()
{
    LOG_METHOD();

    delete activeCard;
    activeCard = nullptr;

    if (view != nullptr)
        view->showDeck(*activeDeck);
}
