#pragma once

#include <memory>
#include "tools/tokenmap.hpp"
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
    
    std::string addCard();
    void deleteCard(const std::string& cardToken);

    void apply();
    void discard();

private:
    ///TODO: avoid friendship
    friend class ControllerProvider;
    friend class CardController;
    Card& getCard(const std::string& cardToken);
    void confirmEditCard();

    IDeckView* view;
    std::shared_ptr<CollectionController> collectionController;

    TokenMap<std::shared_ptr<Card>> tokenMap;

    ///TODO: memento design pattern
    Deck& activeDeck;
    Deck initialDeck;
};
