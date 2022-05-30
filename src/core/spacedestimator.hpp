#pragma once

#include "core/iestimator.hpp"

class SpacedEstimator : public IEstimator
{
public:
    virtual void markEasy(Snapshot &snapshot) override;
    virtual void markGood(Snapshot &snapshot) override;
    virtual void markAgain(Snapshot &snapshot) override;
};
