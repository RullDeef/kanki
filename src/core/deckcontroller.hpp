#pragma once

#include <memory>
#include "model/deck.hpp"
#include "viewapi/ideckview.hpp"

class CollectionController;

class DeckController
{
public:
    DeckController(IDeckView* view, std::shared_ptr<CollectionController> collectionController, const std::string& deckToken);

    ~DeckController();

    DeckController(const DeckController&) = delete;
    DeckController& operator=(const DeckController&) = delete;

    void setDeckName(const std::string& deckName);
    void addCard();
    void editCard(size_t index);
    void deleteCard(size_t index);

    void apply();
    void discard();

private:
    ///TODO: avoid friendship
    friend class ControllerProvider;
    Card& getCard(const std::string& cardToken);

    IDeckView* view;
    std::shared_ptr<CollectionController> collectionController;

    Deck& activeDeck;
    Deck initialDeck;
};
