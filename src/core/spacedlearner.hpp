#pragma once

#include "core/ilearner.hpp"
#include "core/icollectionmanager.hpp"
#include "core/isessionmanager.hpp"

class SpacedLearner : public ILearner
{
public:
    SpacedLearner(ICollectionManager *collectionManager, ISessionManager *sessionManager);

    virtual Card getNextForLearn(UUID deckId) override;
    virtual Card getNextForRepeat(UUID deckId, int paramType) override;

private:
    std::list<Snapshot> getTargets(UUID deckId, int paramType);

    static time_t learningPeriod(int knowledgeDegree);

    ICollectionManager *collectionManager;
    ISessionManager *sessionManager;
};
