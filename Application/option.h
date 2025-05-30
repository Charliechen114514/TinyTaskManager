#pragma once
#include <string>

/**
 * @brief   CommandOption provides an option detections sync until we get the expected
 *          result
 *
 */
namespace CommandOption {

struct OptionHelper {
	std::string title;
	std::string ensure_str;
	std::string deny_str;
	std::string descriptions;
};

bool sync_option(const OptionHelper& op);
};
