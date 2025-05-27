#include "TaskMenu.h"
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
namespace {

static constexpr const char* CMD_HEADER = "Support Command";
static constexpr const char* DESP_HEADER = "Descriptions";

std::string print_help_menu(const std::vector<UiMenu::menu_item_t>& commands) {
	size_t cmd_width = ::strlen(CMD_HEADER);
	size_t desc_width = ::strlen(DESP_HEADER);

	for (const auto& [cmd, desc] : commands) {
		cmd_width = std::max(cmd_width, cmd.first.length());
		desc_width = std::max(desc_width, desc.length());
	}

	std::stringstream ss;

	ss << '+' << std::string(cmd_width + 2, '-') << '+' << std::string(desc_width + 2, '-') << "+\n";
	ss << "| " << std::left << std::setw(cmd_width) << CMD_HEADER << " | "
	   << std::left << std::setw(desc_width) << DESP_HEADER << " |\n";
	ss << '+' << std::string(cmd_width + 2, '-') << '+' << std::string(desc_width + 2, '-') << "+\n";

	for (const auto& [cmd, desc] : commands) {
		ss << "| " << std::left << std::setw(cmd_width) << cmd.first << " | "
		   << std::left << std::setw(desc_width) << desc << " |\n";
	}

	ss << '+' << std::string(cmd_width + 2, '-') << '+' << std::string(desc_width + 2, '-') << "+\n";
	return ss.str();
}

}

std::string UiMenu::menu_for_display() const {
	return print_help_menu(this->lists);
}