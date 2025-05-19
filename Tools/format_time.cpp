#include "format_time.h"
#include "timezone.h"
#include <chrono>
using namespace std::chrono;

static inline std::string __make_format_date(const year_month_day& ymd,
                                             const hh_mm_ss<minutes>& time) {
	return std::format(
	    "{}-{:02}-{:02} {:02}:{:02}",
	    static_cast<int>(ymd.year()),
	    static_cast<unsigned>(ymd.month()),
	    static_cast<unsigned>(ymd.day()),
	    time.hours().count(),
	    time.minutes().count());
}

std::string ChronoTools::
    fromDdlTimeToReadableString(const deadline_raw_t& raw_time) {
	using namespace std;
	using namespace std::chrono;
	auto now = floor<minutes>(raw_time);
	auto days_part = floor<days>(now);
	year_month_day ymd = year_month_day { days_part };

	auto time_since_midnight = now - days_part;
	hh_mm_ss time { time_since_midnight };

	return __make_format_date(ymd, time);
}

deadline_raw_t ChronoTools::localtime_ddl(const deadline_raw_t& raw_time) {
	using namespace std::chrono;
	using namespace std::chrono_literals;

	zoned_time<system_clock::duration> utc_zoned { SYSTEM_TIMEZONE, raw_time };
	auto local = utc_zoned.get_local_time();
	zoned_time<system_clock::duration> target_zoned { "UTC", local };
	return target_zoned.get_sys_time();
}
