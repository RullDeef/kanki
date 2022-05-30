#pragma once

#include "core/editorcontroller.hpp"
#include "core/learnercontroller.hpp"
#include "core/iocontroller.hpp"
#include "cli/view/editorview.hpp"
#include "cli/view/learnerview.hpp"
#include "cli/view/ioview.hpp"
#include "view/editordapter.hpp"
#include "view/learneradapter.hpp"
#include "view/ioviewadapter.hpp"

namespace cli
{
    class Application
    {
    public:
        Application();
        ~Application();

        void setEditorController(EditorController &controller);
        void setLearnerController(LearnerController &controller);
        void setIOController(IOController &controller);

        int run();

    private:
        EditorController *editorController = nullptr;
        EditorViewAdapter *editorViewAdapter;
        EditorView editorView;

        LearnerController *learnerController = nullptr;
        LearnerViewAdapter *learnerViewAdapter;
        LearnerView learnerView;

        IOController *ioController = nullptr;
        IOViewAdapter *ioViewAdapter;
        IOView ioView;
    };
} // namespace cli
