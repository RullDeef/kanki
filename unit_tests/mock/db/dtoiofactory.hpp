#pragma once

#include <gmock/gmock.h>
#include "db/idtoiofactory.hpp"

class MockDTOIOFactory : public IDTOIOFactory
{
public:
    virtual std::unique_ptr<IDTOReader> createReader() override
    {
        auto reader = createReaderProxy();
        return std::unique_ptr<IDTOReader>(reader);
    }

    virtual std::unique_ptr<IDTOWriter> createWriter() override
    {
        auto writer = createWriterProxy();
        return std::unique_ptr<IDTOWriter>(writer);
    }

    MOCK_METHOD0(createReaderProxy, IDTOReader *());
    MOCK_METHOD0(createWriterProxy, IDTOWriter *());
};
