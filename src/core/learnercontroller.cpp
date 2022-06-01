#include "tools/logger.hpp"
#include "learnercontroller.hpp"

LearnerController::LearnerController(std::shared_ptr<ICollectionManager> collectionManager,
                                     std::shared_ptr<ISessionManager> sessionManager)
    : collectionManager(collectionManager), sessionManager(sessionManager)
{
}

void LearnerController::setView(ILearnerView *newView)
{
    view = newView;
}

void LearnerController::setLearner(std::shared_ptr<ILearner> newLearner)
{
    learner = newLearner;
}

void LearnerController::setEstimator(std::shared_ptr<IEstimator> newEstimator)
{
    estimator = newEstimator;
}

void LearnerController::learnNext(UUID deckId)
{
    LOG_METHOD();

    try
    {
        learner->useCollectionManager(collectionManager);
        learner->useSessionManager(sessionManager);

        auto card = learner->getNextForLearn(deckId);

        if (view != nullptr)
            view->showCard(card);
    }
    catch (const std::exception &e)
    {
        if (view != nullptr)
            view->noCardsForLearn();
    }
}

void LearnerController::repeatNext(UUID deckId)
{
    LOG_METHOD();

    auto readingCard = getNextCardFor(deckId, Snapshot::ParamType::READING);
    auto translatingCard = getNextCardFor(deckId, Snapshot::ParamType::TRANSLATION);

    if (readingCard && cardParam == Snapshot::ParamType::READING)
    {
        if (view)
            view->askCard(*readingCard, cardParam);
        cardParam = Snapshot::ParamType::TRANSLATION;
    }
    else if (translatingCard)
    {
        if (view)
            view->askCard(*translatingCard, Snapshot::ParamType::TRANSLATION);
        cardParam = Snapshot::ParamType::READING;
    }
    else if (readingCard)
    {
        if (view)
            view->askCard(*readingCard, Snapshot::ParamType::READING);
    }
    else if (view)
        view->noCardsForRepeat();
}

void LearnerController::confirmLearned(UUID cardId)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card);

    sessionManager->addSnapshot(snapshot);
}

void LearnerController::markEasy(UUID cardId, int paramType)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card, Snapshot::ParamType(paramType));

    estimator->markEasy(snapshot);
    sessionManager->addSnapshot(snapshot);
}

void LearnerController::markGood(UUID cardId, int paramType)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card, Snapshot::ParamType(paramType));

    estimator->markGood(snapshot);
    sessionManager->addSnapshot(snapshot);
}

void LearnerController::markAgain(UUID cardId, int paramType)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card, Snapshot::ParamType(paramType));

    estimator->markAgain(snapshot);
    sessionManager->addSnapshot(snapshot);
}

std::unique_ptr<Card> LearnerController::getNextCardFor(UUID deckId, int paramType)
{
    try
    {
        learner->useCollectionManager(collectionManager);
        learner->useSessionManager(sessionManager);

        /// TODO: change method signature to return unique_ptr
        return std::make_unique<Card>(learner->getNextForRepeat(deckId, paramType));
    }
    catch (const std::exception &e)
    {
        return nullptr;
    }
}
