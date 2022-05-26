#pragma once

#include <memory>
#include "db/idtoreader.hpp"
#include "db/idtowriter.hpp"

class IDTOIOFactory
{
public:
    virtual ~IDTOIOFactory() = default;

    virtual std::unique_ptr<IDTOReader> createReader() = 0;
    virtual std::unique_ptr<IDTOWriter> createWriter() = 0;
};
