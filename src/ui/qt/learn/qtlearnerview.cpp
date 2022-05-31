#include "learn_window.hpp"
#include "info_window.hpp"
#include "qtlearnerview.hpp"

void QtLearnerView::showCard(const CardParams &card)
{
    LearnWindow window(controller, card);
    window.exec();
}

void QtLearnerView::askCard(const CardParams &card, int paramType)
{
    /// TODO: implement
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

void QtLearnerView::setController(std::shared_ptr<LearnerController> newController)
{
    controller = newController;
}
