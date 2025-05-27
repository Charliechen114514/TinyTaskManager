#include "parse_command.h"
#include <cctype>
#include <print>
#include <string_view>
namespace {

Command splitCommandLine(const std::string_view input) {
	std::vector<std::string_view> parts;

	size_t pos = 0;
	while (pos < input.size()) {
		while (pos < input.size() && std::isspace(static_cast<unsigned char>(input[pos]))) {
			++pos;
		}
		if (pos >= input.size())
			break;

		size_t start = pos;
		while (pos < input.size() && !std::isspace(static_cast<unsigned char>(input[pos]))) {
			++pos;
		}

		parts.push_back(input.substr(start, pos - start));
	}

	/* Yet the Main Command must exsited */
	Command command_wrapper;
	if (parts.empty()) {
		return { "", {} };
	} else {
		command_wrapper.cmd = parts[0];
	}
	command_wrapper.args.reserve(parts.size() - 1);
	for (int i = 1; i < parts.size(); i++) {
		command_wrapper.args.emplace_back(parts[i]);
	}

	return command_wrapper;
}
}

Command CommandParser::get_command_from_rawbuffer(const std::string& raw_buffers) {
	return splitCommandLine(raw_buffers);
}

Command CommandParser::parse_buffer_only(const std::string& raw_buffers) {
	Command result = splitCommandLine(raw_buffers);

	if (result.cmd.empty()) {
		throw non_command_found();
	}

	auto handling = hooks.find(result.cmd);
	if (handling == hooks.end()) {
		throw non_match_command();
	} else {
		handling->second(result);
	}

	return result;
}

void CommandParser::parse_buffer_with_errorHooks(const std::string& buffer) {
	try {
		Command cmd = parse_buffer_only(buffer);
	} catch (const parse_exceptions& e) {
		auto functor = exception_handler.find(typeid(e));
		if (functor == exception_handler.end()) {
			/* then, we do not install the error handler for the type */
			throw e; // throw the shit again
		} else {
			functor->second(&e, buffer);
		}
	}
}
