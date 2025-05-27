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
	    std::make_pair("remove", MenuActions::process_delete),
	    "delete the target task"),
	std::make_pair(
	    std::make_pair("exit", MenuActions::process_exit),
	    "exit the program")
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
}
