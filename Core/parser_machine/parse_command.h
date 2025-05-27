/**
 * @file parse_command.h
 * @author Charliechen114514 (chengh1922@mails.jlu.edu.cn)
 * @brief   parse_command file helps implement how to parse
 *          things from remote IO Device
 * @version 0.1
 * @date 2025-05-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "command.h"
#include "parse_exceptions.h"
#include <functional>

#include <typeindex>

template <typename T>
concept is_parse_exception = std::is_base_of_v<parse_exceptions, T>;

/**
 * @brief CommandParser parse the command from IO buffer
 *
 */
struct CommandParser {
	using hookFunction = std::function<void(const Command)>;

	using errorHandleFunction = std::function<void(const parse_exceptions*, const std::string)>;

	inline void install_hook(const std::string& first_target,
	                         const hookFunction func) {
		hooks[first_target] = func;
	}

	template <is_parse_exception ExceptionType>
	/* only the parse error is accept to hook here */
	inline void install_error_hook(errorHandleFunction handler) {
		exception_handler[typeid(ExceptionType)] = handler;
	}

	/**
	 * @brief Get the command from rawbuffer object
	 *
	 * @param raw_buffers the buffer fetch from IO or else
	 * @return 	Command as the result, this will be always meaningful
	 *			for the caller, as we must contains a valid command
	 */
	Command get_command_from_rawbuffer(const std::string& raw_buffers);

	/**
	 *  @brief parse buffer really parse and throw the stuff to the installed hooks
	 *  @note this is exception drive, so you must make hooks of the exception catch
	 *
	 */
	Command parse_buffer_only(const std::string& raw_buffers);

	/**
	 * @brief   parse_buffer_with_errorHooks makes parse with given hooks once
	 * @note    if, non hooks are given, we shell call the default exceptions,
	 *          else, we shell
	 *
	 * @param buffer the buffer waiting parse
	 */
	void parse_buffer_with_errorHooks(const std::string& buffer);

private:
	std::unordered_map<std::string, hookFunction> hooks;
	std::unordered_map<std::type_index, errorHandleFunction> exception_handler;
};