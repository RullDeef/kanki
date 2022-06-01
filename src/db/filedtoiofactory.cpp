#include "db/filedtoiofactory.hpp"
#include "db/filereader.hpp"
#include "db/filewriter.hpp"

FileDTOIOFactory::FileDTOIOFactory(const std::string &filename)
    : filename(filename)
{
}

std::unique_ptr<IDBReader> FileDTOIOFactory::createReader()
{
    return std::unique_ptr<IDBReader>(new FileReader(filename));
}

std::unique_ptr<IDBWriter> FileDTOIOFactory::createWriter()
{
    return std::unique_ptr<IDBWriter>(new FileWriter(filename));
}
