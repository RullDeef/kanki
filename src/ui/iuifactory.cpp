#include "iuifactory.hpp"

void IUIFactory::setEditorController(std::shared_ptr<EditorController> controller)
{
    editorController = controller;
}
void IUIFactory::setLearnerController(std::shared_ptr<LearnerController> controller)
{
    learnerController = controller;
}
void IUIFactory::setIOController(std::shared_ptr<IOController> controller)
{
    ioController = controller;
}

std::shared_ptr<EditorController> IUIFactory::getEditorController()
{
    return editorController;
}

std::shared_ptr<LearnerController> IUIFactory::getLearnerController()
{
    return learnerController;
}

std::shared_ptr<IOController> IUIFactory::getIoController()
{
    return ioController;
}
