#include "Application/application.h"
#include "Application/menu_hooks.h"
#include "Core/TaskLists.h"
#include "Core/TaskViews.h"
#include "Core/Types.h"
#include "IO/interative_io/IOFrontEnd.h"
#include "Tools/format_time.h"
#include <print>

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