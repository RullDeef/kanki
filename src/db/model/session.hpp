#pragma once

#include "tools/uuid.hpp"

class SessionDTO
{
public:
    UUID id;
    time_t startTime;
    time_t endTime;
};
