/**
 * @file TaskMenu.h
 * @author Charliechen114514 (chengh1922@mails.jlu.edu.cn)
 * @brief Task Menu provide a menu to display
 * @version 0.1
 * @date 2025-05-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include "Core/parser_machine/parse_command.h"
#include <string>
#include <vector>
/**
 * @brief   Ui Menu decides which commands should be displayed
 *          and provide avaible commands to the parse machines
 *
 */
struct UiMenu {
	/**
	 * @brief command_pair_t really means the cmd name for matching and hook to do
	 *
	 */
	using command_pair_t = std::pair<std::string, CommandParser::hookFunction>;
	/**
	 * @brief menu_item_t is the menu for display
	 *
	 */
	using menu_item_t = std::pair<command_pair_t, std::string>;
	/**
	 * @brief install_to_parser install all the available command to the menu
	 *
	 * @param parser parser for the ready install
	 */
	inline void install_to_parser(CommandParser& parser) {
		for (const auto& each_pair : lists)
			parser.install_hook(each_pair.first.first, each_pair.first.second);
	}
	/**
	 * @brief install_command_pair install a command pair to the menu
	 *
	 * @param p the command pair to be installed,
	 *          the first is the command name,
	 *          the second is the function to be called
	 */
	inline void install_command_pair(const menu_item_t& p) {
		lists.push_back(p);
	}
	/**
	 * @brief get the menu for display
	 *
	 * @return std::string
	 */
	std::string menu_for_display() const;

private:
	std::vector<menu_item_t> lists;
};
