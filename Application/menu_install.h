/**
 * @file menu_install.h
 * @author Charliechen114514 (chengh1922@mails.jlu.edu.cn)
 * @brief simple expose of the menu install sessions
 * @version 0.1
 * @date 2025-05-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
class UiMenu;
class CommandParser;
/**
 * @brief install the menu instance
 *
 * @param menu from application to install
 */
void install_menu(UiMenu& menu);

/**
 * @brief install the menu hooks for the ui to core
 *
 * @param menu from application to install
 * @param parser waiting the valid options
 */
void install_menu_hooks(UiMenu& menu, CommandParser& parser);