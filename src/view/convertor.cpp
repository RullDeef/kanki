#include "convertor.hpp"

CardParams ParamsConvertor::toCardParams(const Card &card)
{
    CardParams params;

    params.id = card.getId();
    params.symbol = card.getSymbol();
    params.reading = card.getReading();
    params.description = card.getDescription();

    return params;
}

DeckParams ParamsConvertor::toDeckParams(const Deck &deck)
{
    DeckParams params;

    params.id = deck.getId();
    params.name = deck.getName();

    for (auto card : deck)
        params.cards.push_back(toCardParams(card));

    return params;
}

CollectionParams ParamsConvertor::toCollectionParams(const Collection &collection)
{
    CollectionParams params;

    for (auto deck : collection)
    {
        CollectionParams::DeckInfo info;

        info.id = deck.getId();
        info.name = deck.getName();

        params.decks.push_back(info);
    }

    return params;
}
