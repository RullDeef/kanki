#include "fileimporter.hpp"
#include "filereader.hpp"
#include "tools/logger.hpp"
#include "db/model/collectionbuilder.hpp"

DeckCollection FileImporter::importCollection(const std::string &filename)
{
    LOG_METHOD();

    auto reader = FileReader(filename);

    auto dbCollection = reader.readDBCollection();
    size_t decksCount = reader.readCount();
    DBCollectionBuilder collector(dbCollection);

    for (size_t j = 0; j < decksCount; j++)
    {
        auto deckDTO = reader.readDBDeck();
        size_t cardsCount = reader.readCount();
        collector.addDeck(deckDTO);

        for (size_t k = 0; k < cardsCount; k++)
        {
            auto cardDTO = reader.readDBCard();
            collector.addCard(cardDTO);
        }
    }

    return collector.build();
}
