#include <gtest/gtest.h>
#include "tools/logger.hpp"
#include "db/filecollectionrepo.hpp"
#include "mock/db/dtoiofactory.hpp"
#include "mock/db/dtoreader.hpp"
#include "mock/db/dtowriter.hpp"

using ::testing::AtLeast;
using ::testing::Mock;
using ::testing::Return;

TEST(FileCollectionRepository_load, loadEmpty)
{
    Logger::disableLogger();

    MockDTOIOFactory ioFactory;
    auto reader = new MockDTOReader();
    auto writer = new MockDTOWriter();

    Mock::AllowLeak(reader);
    EXPECT_CALL(*reader, readCount)
        .Times(1)
        .WillOnce(Return(0));

    Mock::AllowLeak(writer);
    EXPECT_CALL(*writer, writeCount).Times(1);

    EXPECT_CALL(ioFactory, createReaderProxy)
        .Times(1)
        .WillOnce(Return(reader));
    EXPECT_CALL(ioFactory, createWriterProxy)
        .Times(1)
        .WillOnce(Return(writer));

    FileCollectionRepository repository(&ioFactory);

    EXPECT_EQ(repository.getCollections().size(), 0);
}

TEST(FileCollectionRepository_load, noDecks)
{
    Logger::disableLogger();

    MockDTOIOFactory ioFactory;
    auto reader = new MockDTOReader();
    auto writer = new MockDTOWriter();

    Mock::AllowLeak(reader);
    EXPECT_CALL(*reader, readCount)
        .Times(2)
        .WillOnce(Return(1))
        .WillOnce(Return(0));
    EXPECT_CALL(*reader, readCollectionDTO)
        .Times(1)
        .WillOnce(Return(CollectionDTO{200, L"collection"}));

    Mock::AllowLeak(writer);
    EXPECT_CALL(*writer, writeCount).Times(2);
    EXPECT_CALL(*writer, writeCollectionDTO).Times(1);

    EXPECT_CALL(ioFactory, createReaderProxy)
        .Times(1)
        .WillOnce(Return(reader));
    EXPECT_CALL(ioFactory, createWriterProxy)
        .Times(1)
        .WillOnce(Return(writer));

    FileCollectionRepository repository(&ioFactory);
    auto collections = repository.getCollections();

    EXPECT_EQ(collections.size(), 1);
    EXPECT_EQ(collections.front().getId(), 200);
    EXPECT_EQ(collections.front().size(), 0);
}

TEST(FileCollectionRepository_load, noCards)
{
    Logger::disableLogger();

    MockDTOIOFactory ioFactory;
    auto reader = new MockDTOReader();
    auto writer = new MockDTOWriter();

    Mock::AllowLeak(reader);
    EXPECT_CALL(*reader, readCount)
        .Times(3)
        .WillOnce(Return(1))
        .WillOnce(Return(1))
        .WillOnce(Return(0));
    EXPECT_CALL(*reader, readCollectionDTO)
        .Times(1)
        .WillOnce(Return(CollectionDTO{200, L"collection"}));
    EXPECT_CALL(*reader, readDeckDTO)
        .Times(1)
        .WillOnce(Return(DeckDTO{30, 200, L"brandon"}));

    Mock::AllowLeak(writer);
    EXPECT_CALL(*writer, writeCount).Times(3);
    EXPECT_CALL(*writer, writeCollectionDTO).Times(1);
    EXPECT_CALL(*writer, writeDeckDTO).Times(1);

    EXPECT_CALL(ioFactory, createReaderProxy)
        .Times(1)
        .WillOnce(Return(reader));
    EXPECT_CALL(ioFactory, createWriterProxy)
        .Times(1)
        .WillOnce(Return(writer));

    FileCollectionRepository repository(&ioFactory);
    auto collections = repository.getCollections();
    auto collection = collections.front();
    auto deck = *collection.begin();

    EXPECT_EQ(collections.size(), 1);
    EXPECT_EQ(collection.getId(), 200);
    EXPECT_EQ(collection.size(), 1);
    EXPECT_EQ(deck.getId(), 30);
    EXPECT_EQ(deck.getName(), L"brandon");
}
