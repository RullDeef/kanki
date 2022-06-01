#include <stdexcept>
#include "solution.hpp"
#include "tools/logger.hpp"

std::shared_ptr<ICollectionRepository> Solution::getCollectionRepository()
{
    if (!collectionRepository)
    {
        ERROR_METHOD("collection repository not provided");
        throw std::runtime_error("collection repository not provided");
    }

    return collectionRepository;
}

std::shared_ptr<ISessionRepository> Solution::getSessionRepository()
{
    if (!sessionRepository)
    {
        ERROR_METHOD("session repository not provided");
        throw std::runtime_error("session repository not provided");
    }

    return sessionRepository;
}

std::shared_ptr<ILearner> Solution::getLearner()
{
    if (!learner)
    {
        ERROR_METHOD("learner not provided");
        throw std::runtime_error("learner not provided");
    }

    return learner;
}

std::shared_ptr<IEstimator> Solution::getEstimator()
{
    if (!estimator)
    {
        ERROR_METHOD("estimator not provided");
        throw std::runtime_error("estimator not provided");
    }

    return estimator;
}

std::shared_ptr<IImporter> Solution::getImporter()
{
    if (!importer)
    {
        ERROR_METHOD("importer not provided");
        throw std::runtime_error("importer not provided");
    }

    return importer;
}

std::shared_ptr<IExporter> Solution::getExporter()
{
    if (!exporter)
    {
        ERROR_METHOD("exporter not provided");
        throw std::runtime_error("exporter not provided");
    }

    return exporter;
}

std::shared_ptr<IUIFactory> Solution::getUIFactory()
{
    if (!uiFactory)
    {
        ERROR_METHOD("ui factory not provided");
        throw std::runtime_error("ui factory not provided");
    }

    return uiFactory;
}

void Solution::registerCollectionRepository(std::shared_ptr<ICollectionRepository> repository)
{
    collectionRepository = repository;
}

void Solution::registerSessionRepository(std::shared_ptr<ISessionRepository> repository)
{
    sessionRepository = repository;
}

void Solution::registerLearner(std::shared_ptr<ILearner> newLearner)
{
    learner = newLearner;
}

void Solution::registerEstimator(std::shared_ptr<IEstimator> newEstimator)
{
    estimator = newEstimator;
}

void Solution::registerImporter(std::shared_ptr<IImporter> newImporter)
{
    importer = newImporter;
}

void Solution::registerExporter(std::shared_ptr<IExporter> newExporter)
{
    exporter = newExporter;
}

void Solution::registerUIFactory(std::shared_ptr<IUIFactory> newUiFactory)
{
    uiFactory = newUiFactory;
}
