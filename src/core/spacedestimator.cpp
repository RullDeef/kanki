#include "tools/logger.hpp"
#include "spacedestimator.hpp"

void SpacedEstimator::markEasy(Snapshot &snapshot)
{
    /// TODO: implement correctly
    LOG_METHOD();

    snapshot.setKnowledgeDegree(2);
}

void SpacedEstimator::markGood(Snapshot &snapshot)
{
    /// TODO: implement correctly
    LOG_METHOD();

    snapshot.setKnowledgeDegree(1);
}

void SpacedEstimator::markAgain(Snapshot &snapshot)
{
    /// TODO: implement correctly
    LOG_METHOD();

    snapshot.setKnowledgeDegree(0);
}
