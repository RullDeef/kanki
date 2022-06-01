#include <gtest/gtest.h>
#include "tools/logger.hpp"
#include "db/filecollectionrepo.hpp"
#include "mock/db/dtoiofactory.hpp"
#include "mock/db/dtoreader.hpp"
#include "mock/db/dtowriter.hpp"

using ::testing::AtLeast;
using ::testing::Mock;
using ::testing::Return;
using ::testing::Sequence;

static UUID getId(uint8_t index)
{
    std::array<uint8_t, 16> id10value = {
        0x00, 0x00, 0x00, index,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    return id10value;
}

TEST(FileCollectionRepository_load, empty)
{
    Logger::disableLogger();

    MockDTOReader reader;
    MockDTOIOFactory factory;

    EXPECT_CALL(reader, readCount)
        .WillOnce(Return(0));

    FileCollectionRepository repository;

    EXPECT_NO_THROW(repository.load(reader));

    EXPECT_EQ(repository.getCollections().size(), 0);
}

TEST(FileCollectionRepository_load, noDecks)
{
    Logger::disableLogger();

    MockDTOReader reader;

    EXPECT_CALL(reader, readCount)
        .WillOnce(Return(1))
        .WillOnce(Return(0));
    EXPECT_CALL(reader, readDBCollection)
        .WillOnce(Return(DBDeckCollection{getId(200), L"collection"}));

    FileCollectionRepository repository;

    EXPECT_NO_THROW(repository.load(reader));

    auto collections = repository.getCollections();

    EXPECT_EQ(collections.size(), 1);
    EXPECT_EQ(collections.front().getId(), getId(200));
    EXPECT_EQ(collections.front().size(), 0);
}

TEST(FileCollectionRepository_load, noCards)
{
    Logger::disableLogger();

    MockDTOReader reader;

    EXPECT_CALL(reader, readCount)
        .WillOnce(Return(1))
        .WillOnce(Return(1))
        .WillOnce(Return(0));
    EXPECT_CALL(reader, readDBCollection)
        .WillOnce(Return(DBDeckCollection{getId(200), L"collection"}));
    EXPECT_CALL(reader, readDBDeck)
        .WillOnce(Return(DBDeck{getId(30), getId(200), L"brandon"}));

    FileCollectionRepository repository;

    EXPECT_NO_THROW(repository.load(reader));

    auto collections = repository.getCollections();
    auto collection = collections.front();
    auto deck = *collection.begin();

    EXPECT_EQ(collections.size(), 1);
    EXPECT_EQ(collection.getId(), getId(200));
    EXPECT_EQ(collection.size(), 1);
    EXPECT_EQ(deck.getId(), getId(30));
    EXPECT_EQ(deck.getName(), L"brandon");
}

TEST(FileCollectionRepository_load, twoDecksfourCards)
{
    Logger::disableLogger();

    MockDTOReader reader;

    EXPECT_CALL(reader, readCount)
        .WillOnce(Return(1))
        .WillOnce(Return(2))
        .WillOnce(Return(2))
        .WillOnce(Return(2));
    EXPECT_CALL(reader, readDBCollection)
        .WillOnce(Return(DBDeckCollection{getId(203), L"collection"}));
    EXPECT_CALL(reader, readDBDeck)
        .WillOnce(Return(DBDeck{getId(31), getId(203), L"brandon"}))
        .WillOnce(Return(DBDeck{getId(32), getId(203), L"nikola"}));
    EXPECT_CALL(reader, readDBCard)
        .WillOnce(Return(DBCard{getId(64), getId(31), L"sym1", L"rea1", L"des1"}))
        .WillOnce(Return(DBCard{getId(65), getId(31), L"sym2", L"rea2", L"des2"}))
        .WillOnce(Return(DBCard{getId(66), getId(32), L"sym3", L"rea3", L"des3"}))
        .WillOnce(Return(DBCard{getId(67), getId(32), L"sym4", L"rea4", L"des4"}));

    FileCollectionRepository repository;

    EXPECT_NO_THROW(repository.load(reader));

    auto collections = repository.getCollections();
    auto collection = collections.front();
    auto iter = collection.begin();
    auto deck1 = *iter;
    auto card1 = *deck1.getCardById(getId(64));
    auto card2 = *deck1.getCardById(getId(65));
    std::advance(iter, 1);
    auto deck2 = *iter;
    auto card3 = *deck2.getCardById(getId(66));
    auto card4 = *deck2.getCardById(getId(67));

    EXPECT_EQ(collections.size(), 1);

    EXPECT_EQ(collection.getId(), getId(203));
    EXPECT_EQ(collection.size(), 2);

    EXPECT_EQ(deck1.getId(), getId(31));
    EXPECT_EQ(deck1.getName(), L"brandon");

    EXPECT_EQ(deck2.getId(), getId(32));
    EXPECT_EQ(deck2.getName(), L"nikola");

    EXPECT_EQ(card1, Card(getId(64), L"sym1", L"rea1", L"des1"));
    EXPECT_EQ(card2, Card(getId(65), L"sym2", L"rea2", L"des2"));
    EXPECT_EQ(card3, Card(getId(66), L"sym3", L"rea3", L"des3"));
    EXPECT_EQ(card4, Card(getId(67), L"sym4", L"rea4", L"des4"));
}

TEST(FileCollectionRepository_dump, empty)
{
    Logger::disableLogger();

    MockDTOWriter writer;

    EXPECT_CALL(writer, writeCount(0));

    FileCollectionRepository repository;

    repository.dump(writer);
}

TEST(FileCollectionRepository_dump, noDecks)
{
    Logger::disableLogger();

    MockDTOReader reader;
    MockDTOWriter writer;

    DBDeckCollection dbCollection{getId(1), L"col"};

    EXPECT_CALL(reader, readCount)
        .WillOnce(Return(1))
        .WillOnce(Return(0));
    EXPECT_CALL(reader, readDBCollection)
        .WillOnce(Return(dbCollection));

    Sequence s;

    EXPECT_CALL(writer, writeCount(1))
        .InSequence(s);
    EXPECT_CALL(writer, writeDBCollection(dbCollection))
        .InSequence(s);
    EXPECT_CALL(writer, writeCount(0))
        .InSequence(s);

    FileCollectionRepository repository;

    EXPECT_NO_THROW(repository.load(reader));
    EXPECT_NO_THROW(repository.dump(writer));
}

TEST(FileCollectionRepository_dump, noCards)
{
    Logger::disableLogger();

    MockDTOReader reader;
    MockDTOWriter writer;

    DBDeckCollection dbCollection{getId(200), L"collection"};
    DBDeck deckDTO{getId(30), getId(200), L"brandon"};

    EXPECT_CALL(reader, readCount)
        .WillOnce(Return(1))
        .WillOnce(Return(1))
        .WillOnce(Return(0));
    EXPECT_CALL(reader, readDBCollection)
        .WillOnce(Return(dbCollection));
    EXPECT_CALL(reader, readDBDeck)
        .WillOnce(Return(deckDTO));

    Sequence cntS;

    EXPECT_CALL(writer, writeCount(1))
        .InSequence(cntS);
    EXPECT_CALL(writer, writeCount(1))
        .InSequence(cntS);
    EXPECT_CALL(writer, writeCount(0))
        .InSequence(cntS);

    EXPECT_CALL(writer, writeDBCollection(dbCollection));
    EXPECT_CALL(writer, writeDBDeck(deckDTO));

    FileCollectionRepository repository;

    EXPECT_NO_THROW(repository.load(reader));
    EXPECT_NO_THROW(repository.dump(writer));
}
