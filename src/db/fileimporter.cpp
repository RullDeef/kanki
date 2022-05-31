#include "fileimporter.hpp"
#include "filereader.hpp"
#include "tools/logger.hpp"
#include "db/model/collectionbuilder.hpp"

DeckCollection FileImporter::importCollection(const std::string &filename)
{
    LOG_METHOD();

    auto reader = FileReader(filename);

    auto collectionDTO = reader.readCollectionDTO();
    size_t decksCount = reader.readCount();
    DTOCollectionBuilder collector(collectionDTO);

    for (size_t j = 0; j < decksCount; j++)
    {
        auto deckDTO = reader.readDeckDTO();
        size_t cardsCount = reader.readCount();
        collector.addDeckDTO(deckDTO);

        for (size_t k = 0; k < cardsCount; k++)
        {
            auto cardDTO = reader.readCardDTO();
            collector.addCardDTO(cardDTO);
        }
    }

    return collector.build();
}
