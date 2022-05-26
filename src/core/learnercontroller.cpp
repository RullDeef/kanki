#include "tools/logger.hpp"
#include "learnercontroller.hpp"

LearnerController::LearnerController(ICollectionManager *collectionManager, ISessionManager *sessionManager)
    : collectionManager(collectionManager), sessionManager(sessionManager)
{
}

void LearnerController::setView(ILearnerView *newView)
{
    view = newView;
}

void LearnerController::setLearner(ILearner *newLearner)
{
    learner = newLearner;
}

void LearnerController::setEstimator(IEstimator *newEstimator)
{
    estimator = newEstimator;
}

void LearnerController::learnNext(size_t deckId)
{
    LOG_METHOD();

    try
    {
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

void LearnerController::repeatNext(size_t deckId)
{
    LOG_METHOD();

    try
    {
        auto card = learner->getNextForRepeat(deckId);

        if (view != nullptr)
            view->askCard(card);
    }
    catch (const std::exception &e)
    {
        if (view != nullptr)
            view->noCardsForRepeat();
    }
}

void LearnerController::confirmLearned(size_t cardId)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card, Snapshot::ParamType::READING); /// TODO: implement param type

    sessionManager->addSnapshot(snapshot);
}

void LearnerController::markEasy(size_t cardId)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card, Snapshot::ParamType::READING);

    estimator->markEasy(snapshot);
    sessionManager->addSnapshot(snapshot);
}

void LearnerController::markGood(size_t cardId)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card, Snapshot::ParamType::READING);

    estimator->markGood(snapshot);
    sessionManager->addSnapshot(snapshot);
}

void LearnerController::markAgain(size_t cardId)
{
    LOG_METHOD();

    Card card = collectionManager->getCardById(cardId);
    Snapshot snapshot(card, Snapshot::ParamType::READING);

    estimator->markAgain(snapshot);
    sessionManager->addSnapshot(snapshot);
}
