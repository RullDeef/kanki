#pragma once

#include "model/card.hpp"
#include "model/deck.hpp"
#include "model/collection.hpp"
#include "cardparams.hpp"
#include "deckparams.hpp"
#include "collectionparams.hpp"

class ParamsConvertor
{
public:
    CardParams toCardParams(const Card &card);
    DeckParams toDeckParams(const Deck &deck);
    CollectionParams toCollectionParams(const Collection &collection);
};
