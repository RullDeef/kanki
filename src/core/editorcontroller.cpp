#include <algorithm>
#include "tools/logger.hpp"
#include "editorcontroller.hpp"

EditorController::EditorController(ICollectionManager *collectionManager)
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
    delete activeCollection;
    activeCollection = new Collection(idGenerator());

    if (view != nullptr)
        view->showCollection(*activeCollection);
}

void EditorController::editCollection()
{
    LOG_METHOD();

    delete activeCollection;
    activeCollection = new Collection(collectionManager->getActiveCollection());

    if (view != nullptr)
        view->showCollection(*activeCollection);
}

void EditorController::editCollection(size_t id)
{
    LOG_METHOD();

    delete activeCollection;
    activeCollection = new Collection(collectionManager->getCollectionById(id));

    if (view != nullptr)
        view->showCollection(*activeCollection);
}

void EditorController::saveActiveCollection()
{
    LOG_METHOD();

    collectionManager->saveCollection(*activeCollection);
    /// WARNING: WIGGLE WIGGLE THINGS
}

void EditorController::rejectActiveCollection()
{
    LOG_METHOD();

    delete activeCollection;
    activeCollection = nullptr;
}

void EditorController::addDeck()
{
    delete activeDeck;
    activeDeck = new Deck(idGenerator());

    if (view != nullptr)
        view->showDeck(*activeDeck);
}

void EditorController::editDeck(size_t deckId)
{
    delete activeDeck;

    /// TODO: exception handling
    activeDeck = new Deck(*activeCollection->getDeckById(deckId));

    if (view != nullptr)
        view->showDeck(*activeDeck);
}

void EditorController::addCard()
{
    delete activeCard;
    activeCard = new Card(idGenerator());

    if (view != nullptr)
        view->showCard(*activeCard);
}

void EditorController::editCard(size_t cardId)
{
    delete activeCard;

    /// TODO: exception handling
    activeCard = new Card(*activeDeck->getCardById(cardId));

    if (view != nullptr)
        view->showCard(*activeCard);
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

void EditorController::removeDeck(size_t deckId)
{
    activeCollection->removeDeckById(deckId);

    if (view != nullptr)
        view->showCollection(*activeCollection);
}

void EditorController::removeCard(size_t cardId)
{
    activeDeck->removeCardById(cardId);

    if (view != nullptr)
        view->showDeck(*activeDeck);
}

void EditorController::setDeckName(const std::wstring &newName)
{
    if (activeDeck != nullptr)
        activeDeck->setName(newName);
}

void EditorController::setCardSymbol(const std::wstring &value)
{
    if (activeCard != nullptr)
        activeCard->setSymbol(value);
}

void EditorController::setCardReading(const std::wstring &value)
{
    if (activeCard != nullptr)
        activeCard->setReading(value);
}

void EditorController::setCardDescription(const std::wstring &value)
{
    if (activeCard != nullptr)
        activeCard->setDescription(value);
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
