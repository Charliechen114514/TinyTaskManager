#include "Ui/TaskMenu.h"
#include "application.h"
#include "menu_hooks.h"
namespace {
/**
 * @brief commands here provides the menu waiting for the install
 *
 */
std::vector<UiMenu::menu_item_t> commands = {
	std::make_pair(
	    std::make_pair("help", MenuActions::show_help),
	    "Show the help here"),
	std::make_pair(
	    std::make_pair("list", MenuActions::process_list),
	    "List all the commands"),
	std::make_pair(
	    std::make_pair("add", MenuActions::process_add),
	    "install new tasks"),
	std::make_pair(
	    std::make_pair("delete", MenuActions::process_delete),
	    "delete the target task"),
	std::make_pair(
	    std::make_pair("exit", MenuActions::process_exit),
	    "exit the program"),
	std::make_pair(
	    std::make_pair("load", MenuActions::process_load),
	    "load from the remote file"),
	std::make_pair(
	    std::make_pair("store", MenuActions::process_store),
	    "store the current list to the remote"),
	std::make_pair(
	    std::make_pair("filter", MenuActions::process_filters),
	    "filter with target search expressions")
};
}

/* install the menu */
void install_menu(UiMenu& menu) {
	for (const auto& command : commands)
		menu.install_command_pair(command);
}

void install_menu_hooks(UiMenu& menu, CommandParser& parser) {
	menu.install_to_parser(parser);
	parser.install_error_hook<non_match_command>(MenuActions::handle_non_match);
	parser.install_error_hook<argument_count_mismatch>(MenuActions::handle_arg_count_error);
	parser.install_error_hook<argument_invalid>(MenuActions::handle_arg_count_error);
}
