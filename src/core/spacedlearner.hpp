#pragma once

#include "core/ilearner.hpp"
#include "core/icollectionmanager.hpp"
#include "core/isessionmanager.hpp"

class SpacedLearner : public ILearner
{
public:
    SpacedLearner(ICollectionManager *collectionManager, ISessionManager *sessionManager);

    virtual Card getNextForLearn(size_t deckId) override;
    virtual Card getNextForRepeat(size_t deckId) override;

private:
    std::list<Snapshot> getTargets(size_t deckId);

    ICollectionManager *collectionManager;
    ISessionManager *sessionManager;
};
