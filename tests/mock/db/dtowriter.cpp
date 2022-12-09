#include "dtowriter.hpp"
#include "db/model/collectionparser.hpp"

using ::testing::Sequence;

void MockDTOWriter::expectWrite(const std::initializer_list<DeckCollection> &collections)
{
    Sequence s;

    EXPECT_CALL(*this, writeCount(collections.size()))
        .InSequence(s);

    for (const auto &collection : collections)
    {
        DBCollectionParser parser(collection);

        EXPECT_CALL(*this, writeDBCollection(parser.getCollectionDTO()))
            .InSequence(s);

        EXPECT_CALL(*this, writeCount(parser.getDeckIds().size()))
            .InSequence(s);

        for (const auto &deck_id : parser.getDeckIds())
        {
            EXPECT_CALL(*this, writeDBDeck(parser.getDeckDTO(deck_id)))
                .InSequence(s);

            EXPECT_CALL(*this, writeCount(parser.getCardIds(deck_id).size()))
                .InSequence(s);

            for (const auto &card_id : parser.getCardIds(deck_id))
            {
                EXPECT_CALL(*this, writeDBCard(parser.getCardDTO(card_id)))
                    .InSequence(s);
            }
        }
    }
}
