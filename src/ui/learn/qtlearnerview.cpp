#include "learn_window.hpp"
#include "info_window.hpp"
#include "qtlearnerview.hpp"

void QtLearnerView::showCard(const Card &card)
{
    LearnWindow window(*controller, card);
    window.exec();
}

void QtLearnerView::askCard(const Card &card)
{
    emit showSnapshotSignal(card);
}

void QtLearnerView::noCardsForLearn()
{
    InfoWindow window("Все карточки в этой колоде<br>уже изучены");
    window.exec();
}

void QtLearnerView::noCardsForRepeat()
{
    InfoWindow window("Нет карточек<br>для повторения");
    window.show();
}

void QtLearnerView::setController(LearnerController *newController)
{
    controller = newController;
}
