#include "IO/interative_io/IOFrontEnd.h"
#include "Ui/TaskMenu.h"
#include "menu_install.h"
#include <Application/application.h>
TinyTaskManagerApplication::TinyTaskManagerApplication() {
	app_init();
}

void TinyTaskManagerApplication::app_init() {
	menu = std::make_shared<UiMenu>();
	parser = std::make_shared<CommandParser>();
	shell_io = std::make_shared<StandardShellIO>();
	install_menu(*menu);
	install_menu_hooks(*menu, *parser);
}

void TinyTaskManagerApplication::app_loop() {
	std::string user_buffer;
	while (1) {
		std::cout << menu->menu_for_display();
		/* sync call */
		shell_io->from_io_raw_buffer(user_buffer);

		parser->parse_buffer_with_errorHooks(user_buffer);
	}
}
