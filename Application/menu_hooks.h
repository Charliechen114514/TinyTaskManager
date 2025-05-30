/**
 * @file menu_hooks.h
 * @author Charliechen114514 (chengh1922@mails.jlu.edu.cn)
 * @brief  menu hooks the actions
 * @version 0.1
 * @date 2025-05-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "Core/parser_machine/command.h"
#include "Core/parser_machine/parse_exceptions.h"
namespace MenuActions {

void show_help(const Command& t);
void process_add(const Command& t);
void process_delete(const Command& t);
void process_exit(const Command& t);
void process_list(const Command& t);
void process_filters(const Command& t);

void process_load(const Command& t);
void process_store(const Command& t);

/* error hooks */
void handle_non_match(const parse_exceptions* command, const std::string c);

void handle_arg_count_error(const parse_exceptions* command, const std::string c);

void handle_arg_invalid_error(const parse_exceptions* command, const std::string c);

};
