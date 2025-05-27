#include "Core/parser_machine/parse_command.h"
#include <cassert>
static constexpr const char* NORMAL_CMD = "Hello world!";
static constexpr const char* EMPTY_ARG_CMD = "EmptyArgCmd";
static constexpr const char* NON_CMD = "";
int main() {

	CommandParser parser;
	Command result = parser.get_command_from_rawbuffer(NORMAL_CMD);
	std::cout << result;
	assert(result.cmd == "Hello" && result.args[0] == "world!");

	result = parser.get_command_from_rawbuffer(EMPTY_ARG_CMD);
	assert(result.cmd == EMPTY_ARG_CMD && result.args.empty());

	bool is_fall_in_exception = false;

	try {
		parser.parse_buffer_only(NON_CMD);
	} catch (const non_command_found& e) {
		is_fall_in_exception = true;
	}

	assert(is_fall_in_exception);
}