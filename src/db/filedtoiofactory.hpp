#pragma once

#include <string>
#include "db/idtoiofactory.hpp"

class FileDTOIOFactory : public IDTOIOFactory
{
public:
    FileDTOIOFactory(const std::string& filename);

    virtual std::unique_ptr<IDTOReader> createReader() override;
    virtual std::unique_ptr<IDTOWriter> createWriter() override;

private:
    std::string filename;
};
