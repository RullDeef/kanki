#include "uifactory.hpp"
#include "application.hpp"

int cli::UIFactory::runApplication(int argc, char **argv)
{
    cli::Application app;
    app.setEditorController(getEditorController());
    app.setLearnerController(getLearnerController());
    app.setIOController(getIoController());
    return app.run();
}
