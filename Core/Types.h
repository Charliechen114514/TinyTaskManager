#pragma once
#include <chrono>
/* this is the same as the type: now() returns */
using deadline_raw_t = std::chrono::time_point<
    std::chrono::system_clock,
    std::chrono::nanoseconds>;
