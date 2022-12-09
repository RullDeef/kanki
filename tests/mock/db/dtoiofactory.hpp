#pragma once

#include <gmock/gmock.h>
#include "db/idbiofactory.hpp"

class MockDTOIOFactory : public IDTOIOFactory
{
public:
    virtual std::unique_ptr<IDBReader> createReader() override
    {
        auto reader = createReaderProxy();
        return std::unique_ptr<IDBReader>(reader);
    }

    virtual std::unique_ptr<IDBWriter> createWriter() override
    {
        auto writer = createWriterProxy();
        return std::unique_ptr<IDBWriter>(writer);
    }

    MOCK_METHOD0(createReaderProxy, IDBReader *());
    MOCK_METHOD0(createWriterProxy, IDBWriter *());
};
