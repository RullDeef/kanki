#include <fstream>
#include "tools/convertor.hpp"
#include "collectionexporter.hpp"

CollectionExporter::CollectionExporter(std::shared_ptr<ICollectionRepository> collectionRepo)
    : collectionRepo(collectionRepo)
{}

void CollectionExporter::exportCollection(const Collection& collection)
{
    ///TODO: magic constants
    auto collectionInfo = CollectionInfo(0, "MainCollection");
    collectionRepo->setCollection(collectionInfo);

    for (int deckId = 0; const auto& deck : collection)
    {
        auto deckInfo = DeckInfo(deckId++, collectionInfo.id, deck->getName());
        collectionRepo->setDeck(deckInfo);

        for (int cardId = 0; const auto& card : *deck)
        {
            auto cardInfo = CardInfo(cardId++, deckId,
                card->getSymbol(),
                card->getReading(),
                card->getDescription());

            collectionRepo->setCard(cardInfo);
        }
    }

    ///BUG: collection is not exported
}

Collection CollectionExporter::importCollection()
{
    ///TODO: implement in correct way
    auto filename = "collection.txt";
    std::wifstream file(filename);
    Collection collection;

    do
    {
        std::wstring deckName;
        std::getline(file, deckName);

        size_t deckSize;
        file >> deckSize >> std::ws;

        auto deck = collection.addNewDeck();
        deck->setName(Convert::toString(deckName));

        for (size_t i = 0; i < deckSize; i++)
        {
            std::wstring symbol, reading, description;
            std::getline(file, symbol);
            std::getline(file, reading);
            std::getline(file, description);

            deck->addCard(Card(symbol, reading, description));
        }
        file >> std::ws;
    }
    while (!file.eof());

    return std::move(collection);
}
