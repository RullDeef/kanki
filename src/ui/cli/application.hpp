#pragma once

#include <memory>
#include "core/editorcontroller.hpp"
#include "core/learnercontroller.hpp"
#include "core/iocontroller.hpp"
#include "ui/model/editordapter.hpp"
#include "ui/model/learneradapter.hpp"
#include "ui/model/ioviewadapter.hpp"
#include "editorview.hpp"
#include "learnerview.hpp"
#include "ioview.hpp"

namespace cli
{
    class Application
    {
    public:
        Application();
        ~Application();

        void setEditorController(std::shared_ptr<EditorController> controller);
        void setLearnerController(std::shared_ptr<LearnerController> controller);
        void setIOController(std::shared_ptr<IOController> controller);

        int run();

    private:
        std::shared_ptr<EditorController> editorController;
        EditorViewAdapter *editorViewAdapter;
        EditorView editorView;

        std::shared_ptr<LearnerController> learnerController;
        LearnerViewAdapter *learnerViewAdapter;
        LearnerView learnerView;

        std::shared_ptr<IOController> ioController;
        IOViewAdapter *ioViewAdapter;
        IOView ioView;
    };
} // namespace cli
