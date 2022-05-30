#pragma once

#include "core/editorcontroller.hpp"
#include "core/learnercontroller.hpp"
#include "cli/view/editorview.hpp"
#include "cli/view/learnerview.hpp"
#include "view/editordapter.hpp"
#include "view/learneradapter.hpp"

namespace cli
{
    class Application
    {
    public:
        Application();
        ~Application();

        void setEditorController(EditorController &controller);
        void setLearnerController(LearnerController &controller);

        int run();

    private:
        EditorController *editorController = nullptr;
        EditorViewAdapter *editorViewAdapter;
        EditorView editorView;

        LearnerController *learnerController = nullptr;
        LearnerViewAdapter *learnerViewAdapter;
        LearnerView learnerView;
    };
} // namespace cli
