#pragma once

#include <memory>
#include "core/editorcontroller.hpp"
#include "core/learnercontroller.hpp"
#include "core/iocontroller.hpp"

class IUIFactory
{
public:
    virtual ~IUIFactory() = default;

    void setEditorController(std::shared_ptr<EditorController> controller);
    void setLearnerController(std::shared_ptr<LearnerController> controller);
    void setIOController(std::shared_ptr<IOController> controller);

    virtual int runApplication(int argc, char **argv) = 0;

protected:
    std::shared_ptr<EditorController> getEditorController();
    std::shared_ptr<LearnerController> getLearnerController();
    std::shared_ptr<IOController> getIoController();

private:
    std::shared_ptr<EditorController> editorController;
    std::shared_ptr<LearnerController> learnerController;
    std::shared_ptr<IOController> ioController;
};
