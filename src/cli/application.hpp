#pragma once

#include "core/editorcontroller.hpp"
#include "core/learnercontroller.hpp"
#include "cli/view/editorview.hpp"
#include "view/editordapter.hpp"

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
        LearnerController *learnerController = nullptr;

        EditorViewAdapter* editorViewAdapter;
        EditorView editorView;
    };
} // namespace cli
