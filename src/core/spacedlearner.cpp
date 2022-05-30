#include <cmath>
#include <stdexcept>
#include "tools/time.hpp"
#include "spacedlearner.hpp"

SpacedLearner::SpacedLearner(ICollectionManager *collectionManager, ISessionManager *sessionManager)
    : collectionManager(collectionManager), sessionManager(sessionManager)
{
}

Card SpacedLearner::getNextForLearn(size_t deckId)
{
    auto deck = collectionManager->getDeckById(deckId);

    for (auto card : deck)
    {
        auto snapshots = sessionManager->getAllCardSnapshots(card);

        if (snapshots.empty())
            return card;
    }

    throw std::runtime_error("all cards viewed");
}

Card SpacedLearner::getNextForRepeat(size_t deckId, int paramType)
{
    auto targets = getTargets(deckId, paramType);

    for (const auto snapshot : targets)
    {
        time_t periodValue = learningPeriod(snapshot.getKnowledgeDegree());
        auto timeDelta = clock_spec::from_time_t(periodValue).time_since_epoch();
        
        if (snapshot.getTimeDelta() > timeDelta)
            return snapshot.getCard();
    }

    throw std::runtime_error("no cards for review");
}

std::list<Snapshot> SpacedLearner::getTargets(size_t deckId, int paramType)
{
    std::list<Snapshot> result;
    auto deck = collectionManager->getDeckById(deckId);

    for (auto card : deck)
    {
        auto snapshots = sessionManager->getAllCardSnapshots(card);

        if (snapshots.size() == 0)
            continue;

        Snapshot *recentSnapshot = nullptr;
        for (auto& snapshot : snapshots)
        {
            if (snapshot.getParamType() != paramType)
                continue;
            
            if (recentSnapshot == nullptr || snapshot.getTimePoint() > recentSnapshot->getTimePoint())
                recentSnapshot = &snapshot;
        }

        if (recentSnapshot != nullptr)
            result.push_back(*recentSnapshot);
    }

    return result;
}

time_t SpacedLearner::learningPeriod(int knowledgeDegree)
{
    return std::floor(std::exp(knowledgeDegree / 1.42) - 1);
}
