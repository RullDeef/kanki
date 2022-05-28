#include "tools/logger.hpp"
#include "spacedestimator.hpp"

void SpacedEstimator::markEasy(Snapshot &snapshot)
{
    auto degree = snapshot.getKnowledgeDegree();
    snapshot.setKnowledgeDegree(degree + 2);
}

void SpacedEstimator::markGood(Snapshot &snapshot)
{
    auto degree = snapshot.getKnowledgeDegree();
    snapshot.setKnowledgeDegree(degree + 1);
}

void SpacedEstimator::markAgain(Snapshot &snapshot)
{
    snapshot.setKnowledgeDegree(0);
}
