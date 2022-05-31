#pragma once

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
