#pragma once

#include <algorithm>
#include "tools/logger.hpp"
#include "tools/idgenerator.hpp"
#include "model/card.hpp"
#include "model/deck.hpp"
#include "model/collection.hpp"
#include "core/ieditorview.hpp"
#include "core/icollectionmanager.hpp"

class EditorController
{
public:
    EditorController(ICollectionManager* collectionManager)
        : collectionManager(collectionManager)
    {}

    ~EditorController() {
        delete activeCollection;
        delete activeDeck;
        delete activeCard;
    }

    void setView(IEditorView* newView) {
        view = newView;
    }

    void addCollection() {
        delete activeCollection;
        activeCollection = new Collection(idGenerator());

        if (view != nullptr)
            view->showCollection(*activeCollection);
    }

    void editCollection() {
        LOG_METHOD();

        delete activeCollection;
        activeCollection = new Collection(collectionManager->getActiveCollection());

        if (view != nullptr)
            view->showCollection(*activeCollection);
    }

    void editCollection(size_t id) {
        LOG_METHOD();

        delete activeCollection;
        activeCollection = new Collection(collectionManager->getCollectionById(id));

        if (view != nullptr)
            view->showCollection(*activeCollection);
    }

    void saveActiveCollection() {
        LOG_METHOD();

        collectionManager->saveCollection(*activeCollection);
        ///WARNING: WIGGLE WIGGLE THINGS
    }

    void rejectActiveCollection() {
        LOG_METHOD();

        delete activeCollection;
        activeCollection = nullptr;
    }

    void addDeck() {
        delete activeDeck;
        activeDeck = new Deck(idGenerator());

        if (view != nullptr)
            view->showDeck(*activeDeck);
    }

    void editDeck(size_t deckId) {
        delete activeDeck;
        
        ///TODO: exception handling
        activeDeck = new Deck(*activeCollection->getDeckById(deckId));

        if (view != nullptr)
            view->showDeck(*activeDeck);
    }

    void addCard() {
        delete activeCard;
        activeCard = new Card(idGenerator());

        if (view != nullptr)
            view->showCard(*activeCard);
    }

    void editCard(size_t cardId) {
        delete activeCard;
        
        ///TODO: exception handling
        activeCard = new Card(*activeDeck->getCardById(cardId));

        if (view != nullptr)
            view->showCard(*activeCard);
    }

    void saveActiveDeck() {
        LOG_METHOD();

        activeCollection->addDeck(*activeDeck);
        delete activeDeck;
        activeDeck = nullptr;

        if (view != nullptr)
            view->showCollection(*activeCollection);
    }

    void rejectActiveDeck() {
        LOG_METHOD();

        delete activeDeck;
        activeDeck = nullptr;

        if (view != nullptr)
            view->showCollection(*activeCollection);
    }

    void removeDeck(size_t deckId) {
        activeCollection->removeDeckById(deckId);

        if (view != nullptr)
            view->showCollection(*activeCollection);
    }

    void removeCard(size_t cardId) {
        activeDeck->removeCardById(cardId);

        if (view != nullptr)
            view->showDeck(*activeDeck);
    }

    void setDeckName(const std::wstring& newName) {
        if (activeDeck != nullptr)
            activeDeck->setName(newName);
    }

    void setCardSymbol(const std::wstring& value) {
        if (activeCard != nullptr)
            activeCard->setSymbol(value);
    }

    void setCardReading(const std::wstring& value) {
        if (activeCard != nullptr)
            activeCard->setReading(value);
    }

    void setCardDescription(const std::wstring& value) {
        if (activeCard != nullptr)
            activeCard->setDescription(value);
    }

    void saveActiveCard() {
        LOG_METHOD();

        activeDeck->addCard(*activeCard);
        delete activeCard;
        activeCard = nullptr;

        if (view != nullptr)
            view->showDeck(*activeDeck);
    }

    void rejectActiveCard() {
        LOG_METHOD();

        delete activeCard;
        activeCard = nullptr;

        if (view != nullptr)
            view->showDeck(*activeDeck);
    }

private:
    IEditorView* view = nullptr;

    Collection* activeCollection = nullptr;
    Deck* activeDeck = nullptr;
    Card* activeCard = nullptr;

    ICollectionManager* collectionManager = nullptr;
    IdGenerator idGenerator;
};
