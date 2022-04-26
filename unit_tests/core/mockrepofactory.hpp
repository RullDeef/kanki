#include <gmock/gmock.h>
#include "dbapi/irepofactory.hpp"

class MockSessionRepository : public ISessionRepository
{
public:
    MOCK_METHOD(void, saveSession, (const SessionInfo& session), (override));
    MOCK_METHOD(SessionInfo, getSessionById, (size_t sessionId), (override));
    MOCK_METHOD(std::list<SnapshotInfo>, getSnapshotsInSession, (size_t sessionId), (override));
};

class MockCollectionRepository : public ICollectionRepository
{
public:
    MOCK_METHOD(std::list<size_t>, getCollectionIds, (), (override));
    MOCK_METHOD(std::list<size_t>, getDeckIds, (size_t collectionId), (override));
    MOCK_METHOD(std::list<size_t>, getCardIds, (size_t DeckId), (override));

    MOCK_METHOD(void, setCollection, (const CollectionInfo& collectionInfo), (override));
    MOCK_METHOD(void, setDeck, (const DeckInfo& deckInfo), (override));
    MOCK_METHOD(void, setCard, (const CardInfo& cardInfo), (override));

    MOCK_METHOD(CollectionInfo, getCollection, (size_t collectionId), (override));
    MOCK_METHOD(DeckInfo, getDeck, (size_t deckId), (override));
    MOCK_METHOD(CardInfo, getCard, (size_t cardId), (override));

    MOCK_METHOD(void, deleteCollection, (size_t collectionId), (override));
    MOCK_METHOD(void, deleteDeck, (size_t deckId), (override));
    MOCK_METHOD(void, deleteCard, (size_t cardId), (override));
};

class MockRepoFactory : public IRepositoryFactory {
public:
    MockRepoFactory()
        : collectionRepo(new MockCollectionRepository()), sessionRepo(new MockSessionRepository())
    {}

    virtual std::shared_ptr<ICollectionRepository> getCollectionRepo() override
        { return collectionRepo; }
    virtual std::shared_ptr<ISessionRepository> getSessionRepo() override
        { return sessionRepo; }

private:
    std::shared_ptr<ICollectionRepository> collectionRepo;
    std::shared_ptr<ISessionRepository> sessionRepo;
};
