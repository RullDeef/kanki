#include <stdexcept>
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

Card SpacedLearner::getNextForRepeat(size_t deckId)
{
    auto targets = getTargets(deckId);

    if (targets.empty())
        throw std::runtime_error("no cards for review");

    // выбрать карту из targets
    auto selectedSnapshot = targets.front();
    std::chrono::system_clock::duration maxDuration = selectedSnapshot.getTimeDelta();
    for (const auto snapshot : targets)
    {
        /// TODO: должно быть не время старта, а время до момента повторения
        if (snapshot.getTimeDelta() > maxDuration)
        {
            selectedSnapshot = snapshot;
            maxDuration = snapshot.getTimeDelta();
        }
    }

    return selectedSnapshot.getCard();
}

std::list<Snapshot> SpacedLearner::getTargets(size_t deckId)
{
    std::list<Snapshot> result;
    auto deck = collectionManager->getDeckById(deckId);

    for (auto card : deck)
    {
        auto snapshots = sessionManager->getAllCardSnapshots(card);

        if (snapshots.size() == 0)
            continue;

        Snapshot recentSnapshot = snapshots.front();
        for (auto snapshot : snapshots)
            if (snapshot.getTimePoint() > recentSnapshot.getTimePoint())
                recentSnapshot = snapshot;

        result.push_back(recentSnapshot);
    }

    return result;
}
