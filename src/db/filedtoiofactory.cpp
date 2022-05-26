#include "db/filedtoiofactory.hpp"
#include "db/filereader.hpp"
#include "db/filewriter.hpp"

FileDTOIOFactory::FileDTOIOFactory(const std::string &filename)
    : filename(filename)
{
}

std::unique_ptr<IDTOReader> FileDTOIOFactory::createReader()
{
    return std::unique_ptr<IDTOReader>(new FileReader(filename));
}

std::unique_ptr<IDTOWriter> FileDTOIOFactory::createWriter()
{
    return std::unique_ptr<IDTOWriter>(new FileWriter(filename));
}
