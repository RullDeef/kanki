#pragma once

#include "tools/idgenerator.hpp"
#include "model/card.hpp"
#include "model/deck.hpp"
#include "model/collection.hpp"
#include "core/ieditorview.hpp"
#include "core/icollectionmanager.hpp"

class EditorController
{
public:
    EditorController(ICollectionManager *collectionManager);
    ~EditorController();

    void setView(IEditorView *newView);

    void addCollection();
    void editCollection();
    void editCollection(size_t id);

    void saveActiveCollection();
    void rejectActiveCollection();

    void addDeck();
    void editDeck(size_t deckId);
    void removeDeck(size_t deckId);

    void setDeckName(const std::wstring &newName);

    void saveActiveDeck();
    void rejectActiveDeck();

    void addCard();
    void editCard(size_t cardId);
    void removeCard(size_t cardId);

    void setCardSymbol(const std::wstring &value);
    void setCardReading(const std::wstring &value);
    void setCardDescription(const std::wstring &value);

    void saveActiveCard();
    void rejectActiveCard();

private:
    IEditorView *view = nullptr;

    Collection *activeCollection = nullptr;
    Deck *activeDeck = nullptr;
    Card *activeCard = nullptr;

    ICollectionManager *collectionManager = nullptr;
    IdGenerator idGenerator;
};
