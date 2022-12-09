#include "dtoreader.hpp"
#include "db/model/collectionparser.hpp"

using ::testing::Return;
using ::testing::Sequence;

void MockDTOReader::expectRead(const std::initializer_list<DeckCollection> &collections)
{
    Sequence s;

    EXPECT_CALL(*this, readCount)
        .InSequence(s)
        .WillOnce(Return(collections.size()));

    for (const auto &collection : collections)
    {
        auto parser = DBCollectionParser(collection);

        EXPECT_CALL(*this, readDBCollection)
            .InSequence(s)
            .WillOnce(Return(parser.getCollectionDTO()));

        EXPECT_CALL(*this, readCount)
            .InSequence(s)
            .WillOnce(Return(parser.getDeckIds().size()));

        for (const auto deck_id : parser.getDeckIds())
        {
            EXPECT_CALL(*this, readDBDeck)
                .InSequence(s)
                .WillOnce(Return(parser.getDeckDTO(deck_id)));

            EXPECT_CALL(*this, readCount)
                .InSequence(s)
                .WillOnce(Return(parser.getCardIds(deck_id).size()));

            for (const auto card_id : parser.getCardIds(deck_id))
            {
                EXPECT_CALL(*this, readDBCard)
                    .InSequence(s)
                    .WillOnce(Return(parser.getCardDTO(card_id)));
            }
        }
    }
}
