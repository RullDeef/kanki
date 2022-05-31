#pragma once

#include <memory>
#include "core/icollectionrepository.hpp"
#include "core/isessionrepository.hpp"
#include "core/ilearner.hpp"
#include "core/iestimator.hpp"
#include "core/iimporter.hpp"
#include "core/iexporter.hpp"
#include "ui/iuifactory.hpp"

class Solution
{
public:
    virtual ~Solution() = default;

    std::shared_ptr<ICollectionRepository> getCollectionRepository();
    std::shared_ptr<ISessionRepository> getSessionRepository();

    std::shared_ptr<ILearner> getLearner();
    std::shared_ptr<IEstimator> getEstimator();

    std::shared_ptr<IImporter> getImporter();
    std::shared_ptr<IExporter> getExporter();

    std::shared_ptr<IUIFactory> getUIFactory();

protected:
    void registerCollectionRepository(std::shared_ptr<ICollectionRepository> repository);
    void registerSessionRepository(std::shared_ptr<ISessionRepository> repository);

    void registerLearner(std::shared_ptr<ILearner> newLearner);
    void registerEstimator(std::shared_ptr<IEstimator> newEstimator);

    void registerImporter(std::shared_ptr<IImporter> newImporter);
    void registerExporter(std::shared_ptr<IExporter> newExporter);

    void registerUIFactory(std::shared_ptr<IUIFactory> uiFactory);

private:
    std::shared_ptr<ICollectionRepository> collectionRepository;
    std::shared_ptr<ISessionRepository> sessionRepository;

    std::shared_ptr<ILearner> learner;
    std::shared_ptr<IEstimator> estimator;

    std::shared_ptr<IImporter> importer;
    std::shared_ptr<IExporter> exporter;

    std::shared_ptr<IUIFactory> uiFactory;
};
