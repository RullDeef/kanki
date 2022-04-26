#include <cmath>
#include <chrono>
#include <exception>
#include "tools/logger.hpp"
#include "spacedrepetionlearn.hpp"

SpacedRepetitionLearn::SpacedRepetitionLearn(std::shared_ptr<IModelManager> modelManager)
    : modelManager(modelManager)
{}

Card SpacedRepetitionLearn::getNextForLearn(const Deck& deck)
{
    for (auto card : deck)
    {
        auto snapshots = modelManager->getSnapshots(*card);
        if (snapshots.empty())
            return *card;
    }

    throw std::runtime_error("no new card to learn");
}

CardSnapshot SpacedRepetitionLearn::getNextForRepeat(const Deck& deck, CardSnapshot::ParamType param)
{
    /* Получить следующую карту для повторения */

    WARN_METHOD("implement");

    Card selectedCard;
    int level;
    int minInterval;

    std::list<std::pair<Card, CardSnapshot>> targets;

    for (const auto& card : deck)
    {
        auto snapshots = modelManager->getSnapshots(*card);
        if (!snapshots.empty())
        {
            bool founded = false;
            CardSnapshot lastSnapshot = snapshots.front();
            for (const auto& snapshot : snapshots)
            {
                if (snapshot.getParamType() == param)
                {
                    lastSnapshot = snapshot;
                    founded = true;
                }
            }

            if (founded)
                targets.emplace_back(*card, lastSnapshot);
        }
    }

    if (targets.empty())
        throw std::runtime_error("no cards to repeat");

    // выбрать карту из target
    selectedCard = targets.front().first;
    std::chrono::system_clock::duration minDuration = targets.front().second.getTimeDelta();
    for (const auto [card, snapshot] : targets)
    {
        ///TODO: должно быть не время старта, а время до момента повторения
        if (snapshot.getTimeDelta() < minDuration)
        {
            selectedCard = card;
            minDuration = snapshot.getTimeDelta();
        }
    }

    return CardSnapshot(selectedCard, param, level);
}

int SpacedRepetitionLearn::getCurrInterval(const Card& card, CardSnapshot::ParamType param)
{
    double level = getKnowledgeLevel(card, param);
    double val = std::exp(level / 1.42) - 1;

    val = std::floor(val);

    return val;
}

int SpacedRepetitionLearn::getKnowledgeLevel(const Card& card, CardSnapshot::ParamType param)
{
    int level = 0;
    for (const CardSnapshot& snapshot : modelManager->getSnapshots(card))
        if (snapshot.getParamType() == param)
            level = snapshot.getKnowledgeDegree();

    return level;
}
