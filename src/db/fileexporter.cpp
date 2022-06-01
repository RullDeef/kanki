#include "tools/logger.hpp"
#include "fileexporter.hpp"
#include "filewriter.hpp"
#include "db/model/collectionparser.hpp"

void FileExporter::exportCollection(const std::string &filename, const DeckCollection &collection)
{
    LOG_METHOD();

    auto writer = FileWriter(filename);

    DBCollectionParser parser(collection);
    writer.writeCollectionDTO(parser.getCollectionDTO());

    auto deckIds = parser.getDeckIds();
    writer.writeCount(deckIds.size());

    for (auto deckId : deckIds)
    {
        auto deckDTO = parser.getDeckDTO(deckId);
        writer.writeDeckDTO(deckDTO);

        auto cardIds = parser.getCardIds(deckId);
        writer.writeCount(cardIds.size());

        for (auto cardId : cardIds)
        {
            auto cardDTO = parser.getCardDTO(cardId);
            writer.writeCardDTO(cardDTO);
        }
    }
}
