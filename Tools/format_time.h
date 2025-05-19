#pragma once
#include "Core/Types.h"
#include <string>
namespace ChronoTools {

/**
 * @brief   This is a function that helps to format the time
 *          into a readable string, which is used in the
 *          Task class
 *
 * @param time the time to be formatted
 * @return std::string the formatted string
 */

std::string fromDdlTimeToReadableString(const deadline_raw_t& raw_time);

/**
 * @brief Localtime_ddl is a function that helps to convert from UTC, as
 *        the system time zone, to the local time zone.
 *
 * @param raw_time: at any time from system_clock::now(). or the base operations
 * result on the system clock calculations
 * @return deadline_raw_t
 */
deadline_raw_t localtime_ddl(const deadline_raw_t& raw_time);

}; // namespace ChronoTools