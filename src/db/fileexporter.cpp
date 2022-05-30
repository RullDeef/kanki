#include "tools/logger.hpp"
#include "fileexporter.hpp"
#include "filewriter.hpp"
#include "dto/collectionparser.hpp"

void FileExporter::exportCollection(const std::string &filename, const Collection &collection)
{
    LOG_METHOD();

    auto writer = FileWriter(filename);

    DTOCollectionParser parser(collection);
    writer.writeCollectionDTO(parser.getCollectionDTO());

    auto deckIds = parser.getDeckIds();
    writer.writeCount(deckIds.size());

    for (size_t deckId : deckIds)
    {
        auto deckDTO = parser.getDeckDTO(deckId);
        writer.writeDeckDTO(deckDTO);

        auto cardIds = parser.getCardIds(deckId);
        writer.writeCount(cardIds.size());

        for (size_t cardId : cardIds)
        {
            auto cardDTO = parser.getCardDTO(cardId);
            writer.writeCardDTO(cardDTO);
        }
    }
}
