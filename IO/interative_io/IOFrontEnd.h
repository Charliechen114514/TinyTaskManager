
#pragma once
#include "IO/IOBaseDriver.h"
#include <iostream>

/**
 * @brief console io interfaces
 *
 */
struct StandardShellIO : public IOBase {
	void inline from_io_raw_buffer(std::string& raw_buffer) override {
		std::getline(std::cin, raw_buffer);
	}

	void inline write_raw_buffer_to_io(const std::string& raw_buffer) override {
		std::cout << raw_buffer;
	}
};
