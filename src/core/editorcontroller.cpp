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
    LOG_METHOD();

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
    activeDeck = new Deck(idGenerator());

    if (view != nullptr)
        view->showDeck(*activeDeck);
}

void EditorController::editDeck(size_t deckId)
{
    LOG_METHOD();

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
    activeCard = new Card(idGenerator());

    if (view != nullptr)
        view->showCard(*activeCard);
}

void EditorController::editCard(size_t cardId)
{
    LOG_METHOD();

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

void EditorController::removeDeck(size_t deckId)
{
    LOG_METHOD();

    activeCollection->removeDeckById(deckId);

    if (view != nullptr)
        view->showCollection(*activeCollection);
}

void EditorController::removeCard(size_t cardId)
{
    LOG_METHOD();

    activeDeck->removeCardById(cardId);

    if (view != nullptr)
        view->showDeck(*activeDeck);
}

void EditorController::setDeckName(const std::wstring &newName)
{
    LOG_METHOD();

    if (activeDeck != nullptr)
    {
        activeDeck->setName(newName);

        if (view != nullptr)
            view->showDeck(*activeDeck);
    }
}

void EditorController::setCardSymbol(const std::wstring &value)
{
    LOG_METHOD();

    if (activeCard != nullptr)
    {
        activeCard->setSymbol(value);

        if (view != nullptr)
            view->showCard(*activeCard);
    }
}

void EditorController::setCardReading(const std::wstring &value)
{
    LOG_METHOD();

    if (activeCard != nullptr)
    {
        activeCard->setReading(value);

        if (view != nullptr)
            view->showCard(*activeCard);
    }
}

void EditorController::setCardDescription(const std::wstring &value)
{
    LOG_METHOD();

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
