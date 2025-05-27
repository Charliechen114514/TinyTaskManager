/**
 * @file application.h
 * @author Charliechen114514 (chengh1922@mails.jlu.edu.cn)
 * @brief application level sessions
 * @version 0.1
 * @date 2025-05-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <Tools/class_helper.h>
#include <memory>
class UiMenu;
class CommandParser;
class StandardShellIO;
/**
 * @brief Application Level class abstractions, make it simple in main
 *
 */
class TinyTaskManagerApplication {
public:
	DISABLE_COPY_MOVE(TinyTaskManagerApplication);
	/**
	 * @brief Application loop, this is the main loop of the application
	 *
	 */
	void app_loop();

	/**
	 * @brief Get the menu instance
	 *
	 * @return UiMenu&
	 */
	UiMenu& menu_instance() {
		return *menu;
	}

	/**
	 * @brief Get the parser instance
	 *
	 * @return CommandParser&
	 */
	CommandParser& parser_instance() {
		return *parser;
	}

	/**
	 * @brief Get the shell IO instance
	 *
	 * @return StandardShellIO&
	 */
	StandardShellIO& shell_io_instance() {
		return *shell_io;
	}

	/**
	 * @brief Get the application instance, this is a singleton
	 *
	 * @return TinyTaskManagerApplication&
	 */
	static TinyTaskManagerApplication& application_instance() {
		static TinyTaskManagerApplication app;
		return app;
	}

private:
	/**
	 * @brief Construct a new Tiny Task Manager Application object
	 *
	 */
	TinyTaskManagerApplication();
	/**
	 * @brief Initialize the application, this is called in the constructor
	 *
	 */
	void app_init();
	std::shared_ptr<UiMenu> menu; ///< menu instance, this is the main menu of the application
	std::shared_ptr<CommandParser> parser; ///< parser instance, this is the command parser of the application
	std::shared_ptr<StandardShellIO> shell_io; ///< shell IO instance, this is the IO interface of the application
};