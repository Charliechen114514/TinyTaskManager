#include "menu_hooks.h"
#include "Application/application.h"
#include "Application/help_helper.h"
#include "Core/TaskLists.h"
#include "Core/TaskViews.h"
#include "Core/Types.h"
#include "IO/interative_io/IOFrontEnd.h"
#include "Tools/format_time.h"
#include "Ui/TaskMenu.h"
#include <print>
void MenuActions::show_help(const Command& t) {
	/* this will show the App help page */
	if (t.args.empty())
		std::print("{}", TinyTaskManagerApplication::application_instance().menu_instance().menu_for_display());
	else if (t.args.size() != 1) {
		throw argument_count_mismatch();
	} else {
		auto& ref = helper_dict();
		auto it = ref.find(t.args[0]);
		if (it == ref.end()) {
			throw argument_invalid();
		} else {
			std::println("{}", it->second);
		}
	}
}

void MenuActions::process_add(const Command& t) {
	std::string io_buffer;
	auto& io_instance = TinyTaskManagerApplication::application_instance().shell_io_instance();
	auto builder = Task::TaskBuilder();

	/* name issue */
	std::println("Submit the task name!");
	while (1) {
		io_instance.from_io_raw_buffer(io_buffer);
		if (!io_buffer.empty()) {
			builder.set_name(io_buffer);
			break;
		}
		std::println("We don't accept null names");
		continue;
	}

	/* descriptions */
	std::println("Submit the descriptions!");
	io_instance.from_io_raw_buffer(io_buffer);
	builder.set_description(io_buffer);

	/* set the ddl */
	std::println("Submit the DDL after now's hour!");
	int ddl_hour = 0;
	while (1) {
		io_instance.from_io_raw_buffer(io_buffer);
		try {
			ddl_hour = std::stoi(io_buffer);
			break;
		} catch (const std::invalid_argument&) {
			std::cout << "invalid number! submit a valid number!\n";
		} catch (...) {
			std::cout << "Other Error! submit a valid number!\n";
		}
	}

	deadline_raw_t ddl_t = ChronoTools::localtime_ddl(
	    std::chrono::system_clock::now() + std::chrono::hours(ddl_hour));

	builder.set_ddl(ddl_t);

	/* set the priority */
	std::println("Submit the Priority Number! min is 0(Low) and max is 3 (Urgent)");
	int priority = 0;
	while (1) {
		io_instance.from_io_raw_buffer(io_buffer);
		try {
			priority = std::stoi(io_buffer);
			if (priority >= TaskPriorityMax || priority < 0) {
				std::cout << "invalid priority! submit a valid priority!\n";
				continue;
			}
			builder.set_property(static_cast<TaskPriority>(priority));
			break;
		} catch (const std::invalid_argument&) {
			std::cout << "invalid number! submit a valid number!\n";
		} catch (...) {
			std::cout << "Other Error! submit a valid number!\n";
		}
	}

	auto task_final = builder.build_finish();

	auto& lists = TinyTaskManagerApplication::application_instance().taskLists_instance();
	lists.enqueue_managing_task(task_final);

	/* build finish */
	std::print("build finish! see the following as the result!\n{}", TasksListView::format_tasklists_view({ task_final }));
}
void MenuActions::process_delete(const Command& t) {
	std::println("Hello delete!");
}
void MenuActions::process_exit(const Command& t) {
	std::exit(0);
}
void MenuActions::process_list(const Command& t) {
	auto tasks = TinyTaskManagerApplication::application_instance().taskLists_instance().get_all_tasks();
	std::print("{}", TasksListView::format_tasklists_view(tasks));
}

void MenuActions::process_load(const Command& t) {
	std::println("Hello load!");
}
void MenuActions::process_store(const Command& t) {
	std::println("Hello store");
}

void MenuActions::handle_non_match(const parse_exceptions* command, const std::string c) {
	std::cerr << "Error occurs: " << command->what() << "while trying to parse the command with following: "
	          << c << "\n";
}

void MenuActions::handle_arg_count_error(const parse_exceptions* command, const std::string c) {
	std::cerr << "Error occurs: " << command->what() << "while trying to parse the command with following: "
	          << c << "\n";
}

void MenuActions::handle_arg_invalid_error(const parse_exceptions* command, const std::string c) {
	std::cerr << "Error occurs: " << command->what() << "while trying to parse the command with following: "
	          << c << "\n";
}