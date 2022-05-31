#pragma once

#include "tools/uuid.hpp"

class DBSession
{
public:
    UUID id;
    time_t startTime;
    time_t endTime;
};
