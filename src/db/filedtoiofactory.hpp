#pragma once

#include <string>
#include "db/idbiofactory.hpp"

class FileDTOIOFactory : public IDTOIOFactory
{
public:
    FileDTOIOFactory(const std::string& filename);

    virtual std::unique_ptr<IDBReader> createReader() override;
    virtual std::unique_ptr<IDBWriter> createWriter() override;

private:
    std::string filename;
};
