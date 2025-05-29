#include "Application/task_selector.h"
#include "Core/TaskLists.h"
#include "IO/interative_io/IOFrontEnd.h"
#include "Ui/TaskMenu.h"
#include "menu_install.h"
#include <Application/application.h>
TinyTaskManagerApplication::TinyTaskManagerApplication() {
	app_init();
}

void TinyTaskManagerApplication::load_tasks() {
	auto packs = selector->init_load();
	operating_list->enqueue_managing_tasks(packs);
}

void TinyTaskManagerApplication::app_init() {
	menu = std::make_shared<UiMenu>();
	parser = std::make_shared<CommandParser>();
	shell_io = std::make_shared<StandardShellIO>();
	operating_list = std::make_shared<TaskLists>();
	selector = std::make_shared<TaskListsSelector>();

	install_menu(*menu);
	install_menu_hooks(*menu, *parser);

	load_tasks();
}

void TinyTaskManagerApplication::app_loop() {
	std::string user_buffer;
	std::cout << menu->menu_for_display();
	while (1) {
		shell_io->write_raw_buffer_to_io(CONSOLE_STYLE);
		/* sync call */
		shell_io->from_io_raw_buffer(user_buffer);

		parser->parse_buffer_with_errorHooks(user_buffer);
	}
}
