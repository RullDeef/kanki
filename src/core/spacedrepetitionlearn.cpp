#include "tools/logger.hpp"
#include "spacedrepetitionlearn.hpp"
#include "../dbapi/sessionadapter.hpp"

SpacedRepetitionLearn::SpacedRepetitionLearn(std::shared_ptr<ISessionRepository> repository)
    : repository(repository)
{}

static int counter = 0;
CardSnapshot SpacedRepetitionLearn::getNextForLearn(const Deck& deck)
{
    auto session = SessionAdapter(repository).extractSession(0);

    auto iter = deck.begin();
    std::advance(iter, counter++);

    return CardSnapshot(*iter);
}

CardSnapshot SpacedRepetitionLearn::getNextForRepeat(const Deck& deck)
{

}
