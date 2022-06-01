#pragma once

#include <memory>
#include "core/ilearner.hpp"
#include "core/icollectionmanager.hpp"
#include "core/isessionmanager.hpp"

class SpacedLearner : public ILearner
{
public:
    virtual void useCollectionManager(std::shared_ptr<ICollectionManager> manager) override;
    virtual void useSessionManager(std::shared_ptr<ISessionManager> manager) override;

    virtual Card getNextForLearn(UUID deckId) override;
    virtual Card getNextForRepeat(UUID deckId, int paramType) override;

private:
    std::list<Snapshot> getTargets(UUID deckId, int paramType);

    static time_point calcRepeatingTime(const Snapshot& snapshot);
    static time_t learningPeriod(int knowledgeDegree);

    std::shared_ptr<ICollectionManager> collectionManager;
    std::shared_ptr<ISessionManager> sessionManager;
};
