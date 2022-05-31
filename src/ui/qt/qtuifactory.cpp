#include <QApplication>
#include "qtuifactory.hpp"
#include "main_window.hpp"

int QtUIFactory::runApplication(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window(getEditorController(), getLearnerController());
    window.show();
    return app.exec();
}
