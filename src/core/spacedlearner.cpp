#include <cmath>
#include <stdexcept>
#include "tools/time.hpp"
#include "spacedlearner.hpp"

void SpacedLearner::useCollectionManager(std::shared_ptr<ICollectionManager> manager)
{
    collectionManager = manager;
}

void SpacedLearner::useSessionManager(std::shared_ptr<ISessionManager> manager)
{
    sessionManager = manager;
}

Card SpacedLearner::getNextForLearn(UUID deckId)
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

Card SpacedLearner::getNextForRepeat(UUID deckId, int paramType)
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

std::list<Snapshot> SpacedLearner::getTargets(UUID deckId, int paramType)
{
    std::list<Snapshot> result;
    auto deck = collectionManager->getDeckById(deckId);

    for (auto card : deck)
    {
        auto snapshots = sessionManager->getAllCardSnapshots(card);
        if (snapshots.size() == 0)
            continue;

        Snapshot *recentSnapshot = nullptr;
        for (auto &snapshot : snapshots)
            if ((snapshot.getParamType() == paramType || snapshot.getParamType() == Snapshot::ParamType::NONE)
                && (recentSnapshot == nullptr || snapshot.getTimePoint() > recentSnapshot->getTimePoint()))
                    recentSnapshot = &snapshot;

        if (recentSnapshot != nullptr)
            result.push_back(*recentSnapshot);
    }

    return result;
}

time_t SpacedLearner::learningPeriod(int knowledgeDegree)
{
    return std::floor(std::exp(knowledgeDegree / 1.42) - 1);
}
