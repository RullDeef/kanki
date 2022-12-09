#include <gtest/gtest.h>
#include "db/filecollectionrepo.hpp"
#include "mock/db/dtoiofactory.hpp"
#include "mock/db/dtoreader.hpp"
#include "mock/db/dtowriter.hpp"

#include "builders/collectionbuilder.hpp"
#include "db/model/collectionparser.hpp"

using ::testing::Mock;
using ::testing::Return;
using ::testing::Sequence;

TEST(FileCollectionRepository_load, empty)
{
    MockDTOReader reader;
    reader.expectRead({});

    FileCollectionRepository repository;

    repository.load(reader);

    EXPECT_EQ(repository.getCollections().size(), 0);
}

TEST(FileCollectionRepository_load, noDecks)
{
    auto targetCollection = DeckCollectionBuilder::random(0, 0).build();

    MockDTOReader reader;
    reader.expectRead({targetCollection});

    FileCollectionRepository repository;

    repository.load(reader);

    auto collections = repository.getCollections();
    EXPECT_EQ(collections, std::list{targetCollection});
}

TEST(FileCollectionRepository_load, noCards)
{
    auto targetCollection = DeckCollectionBuilder::random(3, 0).build();

    MockDTOReader reader;
    reader.expectRead({targetCollection});

    FileCollectionRepository repository;

    repository.load(reader);

    auto collections = repository.getCollections();
    EXPECT_EQ(collections, std::list{targetCollection});
}

TEST(FileCollectionRepository_load, twoDecksFourCards)
{
    auto targetCollection = DeckCollectionBuilder::random(2, 2).build();

    MockDTOReader reader;
    reader.expectRead({targetCollection});

    FileCollectionRepository repository;

    EXPECT_NO_THROW(repository.load(reader));

    auto collections = repository.getCollections();
    EXPECT_EQ(collections, std::list{targetCollection});
}

TEST(FileCollectionRepository_dump, empty)
{
    MockDTOWriter writer;
    writer.expectWrite({});

    FileCollectionRepository repository;

    EXPECT_NO_THROW(repository.dump(writer));
}

TEST(FileCollectionRepository_dump, noDecks)
{
    auto targetCollection = DeckCollectionBuilder::random(0, 0).build();

    MockDTOReader reader;
    reader.expectRead({targetCollection});

    MockDTOWriter writer;
    writer.expectWrite({targetCollection});

    FileCollectionRepository repository;

    EXPECT_NO_THROW(repository.load(reader));
    EXPECT_NO_THROW(repository.dump(writer));
}

TEST(FileCollectionRepository_dump, noCards)
{
    auto targetCollection = DeckCollectionBuilder::random(1, 0).build();

    MockDTOReader reader;
    reader.expectRead({targetCollection});

    MockDTOWriter writer;
    writer.expectWrite({targetCollection});

    FileCollectionRepository repository;

    EXPECT_NO_THROW(repository.load(reader));
    EXPECT_NO_THROW(repository.dump(writer));
}
