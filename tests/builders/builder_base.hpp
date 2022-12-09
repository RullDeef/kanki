#pragma once

#include <string>
#include "tools/uuid.hpp"
#include "tools/time.hpp"

UUID gen_random_uuid();
std::wstring gen_random_string(size_t len);
time_point gen_random_time_point(long min_days, long max_days);
