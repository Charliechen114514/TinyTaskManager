#include "command.h"
#include <print>
std::ostream& operator<<(std::ostream& os, const Command& command) {
	std::print("Command fetch: {}; Command Args: ", command.cmd);
	for (const auto& each : command.args) {
		std::print("{} ", each);
	}
	std::println("");
	return os;
}
