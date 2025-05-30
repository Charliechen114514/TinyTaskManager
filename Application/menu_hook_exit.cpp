#include "Application/application.h"
#include "Application/menu_hooks.h"
#include "Application/option.h"
#include "Core/parser_machine/command.h"

static void __process_exit(const Command& t) {
	/* mark the sessoin as the quit status */
	TinyTaskManagerApplication::application_instance().mark_as_quit();

	bool op = CommandOption::sync_option({ "Do you want to save all the changes?",
	                                       "y",
	                                       "n",
	                                       "save the changes" });
	if (!op)
		return; /// session ends
	MenuActions::process_store({});
}

void MenuActions::process_exit(const Command& t) {
	__process_exit(t);
}