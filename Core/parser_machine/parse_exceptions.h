#pragma once
#include <exception>
#include <string>

/**
 * @brief parse excetions happens when parsing from IO
 *
 */
struct parse_exceptions : public std::exception {
	parse_exceptions(const std::string& installed_msg)
	    : message(installed_msg) { }

	virtual const char* what() const noexcept {
		return message.c_str();
	}

protected:
	std::string message;
};

/**
 * @brief 	when exceptions happens, it means  non command is found, which means
 *			cmd empty in Command class
 * @see 	class Command
 *
 */
struct non_command_found : public parse_exceptions {
	non_command_found()
	    : parse_exceptions("You submit no command!\n") { };
};

/**
 * @brief when the command is not match any of the installed hooks, this
 *			exceptions will be thrown, which means the command is not match in any things in menu sessions
 *
 */
struct non_match_command : public parse_exceptions {
	non_match_command()
	    : parse_exceptions("Can not find target command for processing!\n") { };
};

/**
 * @brief when args count is mismatch during the parse, these will be thrown
 *
 */
struct argument_count_mismatch : public parse_exceptions {
	argument_count_mismatch()
	    : parse_exceptions("Mismatching the argument size!\n") { };
};

/**
 * @brief when args provided invalid during the parse, these will be thrown
 *
 */
struct argument_invalid : public parse_exceptions {
	argument_invalid()
	    : parse_exceptions("Argument invalid!\n") { };
};
