#pragma once

#include <memory>
#include "db/idbreader.hpp"
#include "db/idbwriter.hpp"

class IDTOIOFactory
{
public:
    virtual ~IDTOIOFactory() = default;

    virtual std::unique_ptr<IDBReader> createReader() = 0;
    virtual std::unique_ptr<IDBWriter> createWriter() = 0;
};
