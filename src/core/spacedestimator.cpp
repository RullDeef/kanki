#include "tools/logger.hpp"
#include "spacedestimator.hpp"

void SpacedEstimator::markEasy(Snapshot &snapshot)
{
    /// TODO: implement correctly
    auto degree = snapshot.getKnowledgeDegree();
    snapshot.setKnowledgeDegree(degree + 2);
}

void SpacedEstimator::markGood(Snapshot &snapshot)
{
    /// TODO: implement correctly
    auto degree = snapshot.getKnowledgeDegree();
    snapshot.setKnowledgeDegree(degree + 1);
}

void SpacedEstimator::markAgain(Snapshot &snapshot)
{
    /// TODO: implement correctly
    snapshot.setKnowledgeDegree(0);
}
