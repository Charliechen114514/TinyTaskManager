#include "menu_hooks.h"
#include <print>

void MenuActions::handle_non_match(const parse_exceptions* command, const std::string c) {
	std::cerr << "Error occurs: " << command->what() << "while trying to parse the command with following: "
	          << c << "\n";
}

void MenuActions::handle_arg_count_error(const parse_exceptions* command, const std::string c) {
	std::cerr << "Error occurs: " << command->what() << "while trying to parse the command with following: "
	          << c << "\n";
}

void MenuActions::handle_arg_invalid_error(const parse_exceptions* command, const std::string c) {
	std::cerr << "Error occurs: " << command->what() << "while trying to parse the command with following: "
	          << c << "\n";
}