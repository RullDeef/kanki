#include "modeladapter.hpp"

ModelInfoAdapter::ModelInfoAdapter(std::shared_ptr<ICollectionRepository> repository)
    : repository(repository)
{}

Collection ModelInfoAdapter::extractCollection(size_t id)
{
    auto collectionInfo = repository->getCollection(id);
    return extractCollection(collectionInfo);
}

Collection ModelInfoAdapter::extractCollection(const CollectionInfo& collectionInfo)
{
    auto deckIds = repository->getDeckIds(collectionInfo.id);

    Collection collection;

    for (auto deckId : deckIds)
    {
        auto deckInfo = repository->getDeckById(deckId);
        auto cardIds = repository->getCardIds(deckId);

        Deck deck(deckInfo.name);

        for (auto cardId : cardIds)
        {
            auto cardInfo = repository->getCardById(cardId);

            deck.addCard(extractCard(cardInfo));
        }

        collection.addDeck(std::move(deck));
    }

    return std::move(collection);
}

Deck ModelInfoAdapter::extractDeck(size_t id)
{
    auto deckInfo = repository->getDeckById(id);
    return extractDeck(deckInfo);
}

Deck ModelInfoAdapter::extractDeck(const std::string& deckName)
{
    auto deckInfo = repository->getDeckByName(deckName);
    return extractDeck(deckInfo);
}

Deck ModelInfoAdapter::extractDeck(const DeckInfo& deckInfo)
{
    auto deck = Deck(deckInfo.name);
    auto cardIds = repository->getCardIds(deckInfo.id);

    for (auto cardId : cardIds)
    {
        auto cardInfo = repository->getCardById(cardId);
        deck.addCard(extractCard(cardInfo));
    }

    return std::move(deck);
}

Card ModelInfoAdapter::extractCard(size_t id)
{
    auto info = repository->getCardById(id);
    return Card(info.symbol, info.reading, info.description);
}

Card ModelInfoAdapter::extractCard(const CardInfo& cardInfo)
{
    auto info = repository->getCardById(cardInfo.id);
    return Card(info.symbol, info.reading, info.description);
}
