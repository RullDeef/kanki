#pragma once

#include <chrono>

typedef std::chrono::system_clock clock_spec;
using time_point = clock_spec::time_point;
using duration = clock_spec::duration;
