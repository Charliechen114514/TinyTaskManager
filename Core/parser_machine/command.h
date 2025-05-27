#pragma once
#include <iostream>
#include <string>
#include <vector>
/**
 * @brief Command abstractions
 *
 */
struct Command {
	std::string cmd; ///< command from io
	std::vector<std::string> args; ///< args if fines
};

/**
 * @brief this functions just simply override the << for a better display
 *
 * @param os
 * @param c
 * @return std::ostream&
 */
std::ostream& operator<<(std::ostream& os, const Command& c);
