#include "Application/application.h"
#include "Application/menu_hooks.h"
#include "Application/option.h"
#include "Core/TaskLists.h"
#include "IO/interative_io/IOFrontEnd.h"
#include <print>

void MenuActions::process_delete(const Command& t) {
	/* fetch from the remote */
	auto& app_instance = TinyTaskManagerApplication::application_instance();
	StandardShellIO& shell_io = app_instance.shell_io_instance();
	std::string name;
	auto& taskLists = app_instance.taskLists_instance();

	if (t.args.size() == 1) {
		name = t.args[0];
	} else if (t.args.empty()) {
		std::println("Submit the task name for the displays, all the same name will be erased!");
		app_instance.display_shell_format();
		shell_io.from_io_raw_buffer(name);
	} else {
		throw argument_count_mismatch();
	}

	auto results = taskLists.query_with_name(name);
	if (results.empty()) {
		std::println("Can not find the matching name: {} quit the sessions", name);
		return;
	}

	bool op = CommandOption::sync_option({ "These Tasks will be erased! Is this what you expected?",
	                                       "y",
	                                       "n",
	                                       "ensure the delete" });
	if (!op) {
		std::println("quit the delete sessions!");
		return;
	}

	taskLists.dequeue_managing_tasks(results);

	std::println("finish the erase, print list to see the result!");
}