#pragma once
#include <string>
#include <unordered_map>
inline std::unordered_map<std::string, std::string>& helper_dict() {
	static std::unordered_map<std::string, std::string> maps_help {
		{ "help", "show the help main page" },
		{ "add", "add the task for details" },
		{ "delete", "delete the task with given names" },
		{ "list", "show the detailed lists" },
	};
	return maps_help;
}
