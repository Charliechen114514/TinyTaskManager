#include "uuid_generator.h"
#include <iomanip>
#include <random>
#include <sstream>

std::string UUIDTools::gen_uuid() {
	std::random_device rd;
	std::mt19937_64 eng(rd());
	std::uniform_int_distribution<uint64_t> dist;

	uint64_t part1 = dist(eng);
	uint64_t part2 = dist(eng);

	std::ostringstream oss;
	oss << std::hex << std::setfill('0')
	    << std::setw(16) << part1
	    << std::setw(16) << part2;
	return oss.str();
}
