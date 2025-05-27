#include "menu_hooks.h"
#include <print>

void MenuActions::show_help(const Command& t) {
	std::println("Hello help!");
}

void MenuActions::process_add(const Command& t) {
	std::println("Hello add!");
}
void MenuActions::process_delete(const Command& t) {
	std::println("Hello delete!");
}
void MenuActions::process_exit(const Command& t) {
	std::exit(0);
}
void MenuActions::process_list(const Command& t) {
	std::println("Hello list!");
}

void MenuActions::handle_non_match(const parse_exceptions* command, const std::string c) {
	std::cerr << "Error occurs: " << command->what() << "while trying to parse the command with following: \n"
	          << c << "\n";
}
