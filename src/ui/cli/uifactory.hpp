#pragma once

#include "ui/iuifactory.hpp"

namespace cli
{
    class UIFactory : public IUIFactory
    {
    public:
        virtual int runApplication(int argc, char **argv) override;
    };
} // namespace cli
