#pragma once

#include "ui/iuifactory.hpp"

class QtUIFactory : public IUIFactory
{
public:
    virtual int runApplication(int argc, char **argv) override;
};
