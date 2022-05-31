#pragma once

#include <memory>
#include "model/card.hpp"

class ICollectionManager;
class ISessionManager;

class ILearner
{
public:
    virtual ~ILearner() = default;

    virtual void useCollectionManager(std::shared_ptr<ICollectionManager> manager) {}
    virtual void useSessionManager(std::shared_ptr<ISessionManager> manager) {}

    virtual Card getNextForLearn(UUID deckId) = 0;
    virtual Card getNextForRepeat(UUID deckId, int paramType) = 0;
};
