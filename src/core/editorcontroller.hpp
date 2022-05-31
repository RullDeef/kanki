#pragma once

#include "tools/idgenerator.hpp"
#include "model/card.hpp"
#include "model/deck.hpp"
#include "model/deckcollection.hpp"
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
    void editCollection(UUID id);

    void saveActiveCollection();
    void rejectActiveCollection();

    void addDeck();
    void editDeck(UUID deckId);
    void removeDeck(UUID deckId);

    void setDeckName(const std::wstring &newName);

    void saveActiveDeck();
    void rejectActiveDeck();

    void addCard();
    void editCard(UUID cardId);
    void removeCard(UUID cardId);

    void setCardSymbol(const std::wstring &value);
    void setCardReading(const std::wstring &value);
    void setCardDescription(const std::wstring &value);

    void saveActiveCard();
    void rejectActiveCard();

private:
    IEditorView *view = nullptr;

    DeckCollection *activeCollection = nullptr;
    Deck *activeDeck = nullptr;
    Card *activeCard = nullptr;

    ICollectionManager *collectionManager = nullptr;
    IdGenerator idGenerator;
};
