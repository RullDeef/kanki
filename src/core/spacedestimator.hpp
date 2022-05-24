#pragma once

#include "tools/logger.hpp"
#include "core/iestimator.hpp"

class SpacedEstimator : public IEstimator
{
public:
    virtual void markEasy(Snapshot& snapshot) override {
        ///TODO: implement correctly
        LOG_METHOD();

        snapshot.setKnowledgeDegree(2);
    }

    virtual void markGood(Snapshot& snapshot) override {
        ///TODO: implement correctly
        LOG_METHOD();

        snapshot.setKnowledgeDegree(1);
    }

    virtual void markAgain(Snapshot& snapshot) override {
        ///TODO: implement correctly
        LOG_METHOD();

        snapshot.setKnowledgeDegree(0);
    }
};
