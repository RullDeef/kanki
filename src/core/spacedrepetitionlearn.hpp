#pragma once

#include <memory>
#include "ilearnstategy.hpp"
#include "../dbapi/isessionrepo.hpp"

class SpacedRepetitionLearn : public ILearningStrategy
{
public:
    explicit SpacedRepetitionLearn(std::shared_ptr<ISessionRepository> repository);

    virtual CardSnapshot getNextForLearn(const Deck& deck) override;
    virtual CardSnapshot getNextForRepeat(const Deck& deck) override;

private:
    std::shared_ptr<ISessionRepository> repository;
};
