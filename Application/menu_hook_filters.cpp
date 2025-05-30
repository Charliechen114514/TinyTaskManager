#include "Application/application.h"
#include "Application/menu_hooks.h"
#include "Core/TaskExceptions.h"
#include "Core/TaskFilters.h"
#include "Core/TaskLists.h"
#include "Core/TaskViews.h"
#include "IO/interative_io/IOFrontEnd.h"
#include <print>
namespace {
const auto filter_keys = std::vector {
	std::string_view("ddl"),
	std::string_view("name"),
	std::string_view("priority")
};

const auto filter_priority_keys = std::vector {
	std::string_view(">"),
	std::string_view("<"),
	std::string_view("="),
	std::string_view(">="),
	std::string_view("<="),
};

const std::unordered_map<std::string, PriorityFilters::FilterWay> waykey_map {
	{ ">", PriorityFilters::FilterWay::ACCEPT_HIGH },
	{ "<", PriorityFilters::FilterWay::ACCEPT_LOW },
	{ ">=", PriorityFilters::FilterWay::ACCEPT_SAME_HIGH },
	{ "<=", PriorityFilters::FilterWay::ACCEPT_SAME_LOW },
	{ "=", PriorityFilters::FilterWay::ACCEPT_SAME }
};

void dump_key_menu(const typeof(filter_keys)& maps) {
	std::println("These keys are avaliable: ");
	for (const auto& each : maps) {
		std::print("{} ", each);
	}
}

void filter_key_check(const std::string& key, const typeof(filter_keys)& maps) {
	auto it = std::find(filter_keys.begin(), filter_keys.end(), key);
	if (it == filter_keys.cend()) {
		throw InvalidKeyException(key);
	}
}

std::string sync_query_filter_key(const typeof(filter_keys)& maps) {
	auto& app = TinyTaskManagerApplication::application_instance();
	StandardShellIO& io = app.shell_io_instance();
	std::string user_choice;
	while (1) {
		std::println("submit a filter key");
		dump_key_menu(maps);
		app.display_shell_format();
		try {
			io.from_io_raw_buffer(user_choice);
			filter_key_check(user_choice, maps);
			return user_choice;
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			continue;
		}
	}
}

int get_ddl_number() {
	StandardShellIO& io_instance = TinyTaskManagerApplication::application_instance().shell_io_instance();
	std::string io_buffer;
	std::println("Submit the DDL after now's hour!");
	int ddl_hour = 0;
	while (1) {
		io_instance.from_io_raw_buffer(io_buffer);
		try {
			ddl_hour = std::stoi(io_buffer);
			return ddl_hour;
		} catch (const std::invalid_argument&) {
			std::cout << "invalid number! submit a valid number!\n";
		} catch (...) {
			std::cout << "Other Error! submit a valid number!\n";
		}
	}
}

void check_priority_base(const std::string& str) {
	int indicate = std::stoi(str);
	if (indicate < 0 || indicate >= TaskPriorityMax) {
		throw argument_invalid();
	}
}

TaskPriority sync_query_priority() {
	StandardShellIO& io_instance = TinyTaskManagerApplication::application_instance().shell_io_instance();
	std::string io_buffer;
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
			return static_cast<TaskPriority>(priority);
		} catch (const std::invalid_argument&) {
			std::cout << "invalid number! submit a valid number!\n";
		} catch (...) {
			std::cout << "Other Error! submit a valid number!\n";
		}
	}
}

std::pair<TaskPriority, PriorityFilters::FilterWay> get_indicate(const Command& t) {
	/* examples: filter priority INFO > owns as much as 3, which is the most */
	TaskPriority p;
	PriorityFilters::FilterWay way;
	if (t.args.size() > 3) {
		throw argument_count_mismatch();
	}

	if (t.args.size() == 3) {
		/* check the way first */
		try {
			auto it = waykey_map.find(t.args[2]);
			if (it == waykey_map.cend())
				throw argument_invalid();
			way = it->second;
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		do_it_again:
			auto way_str = sync_query_filter_key(filter_priority_keys);
			auto it = waykey_map.find(t.args[2]);

			if (it == waykey_map.cend()) {
				std::println("Still Missing key of {}", way_str);
				goto do_it_again;
			}
		}
	}

	if (t.args.size() >= 2) {
		try {
			check_priority_base(t.args[1]);
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			/* back to the submit of priority string */
			p = sync_query_priority();
		}
	}

	return { p, way };
}

}

void MenuActions::process_filters(const Command& t) {
	const auto& tasks = TinyTaskManagerApplication::application_instance().taskLists_instance();
	std::string filter;
	TaskFilterDrive driver;
	std::shared_ptr<AbstractTaskFilters> filters;
	if (t.args.empty()) {
		filter = sync_query_filter_key(filter_keys);
	} else {
		filter = t.args[0];
	}

	if (filter == "name") {
		/* check the non more args */
		if (t.args.size() > 2) {
			throw argument_count_mismatch();
		} else if (t.args.size() == 2) {
			filters = std::make_shared<NameContainsFilter>(t.args[1]);
		} else {
			/* get the name from console */
			StandardShellIO& io = TinyTaskManagerApplication::application_instance().shell_io_instance();
			std::string name;
			io.from_io_raw_buffer(name);
			filters = std::make_shared<NameContainsFilter>(name);
		}

	} else if (filter == "ddl") {
		filters = std::make_shared<LeavingTimeFilters>(
		    std::chrono::duration_cast<std::chrono::seconds>(
		        std::chrono::hours(get_ddl_number())));
	} else if (filter == "priority") {
		/* first , query if the base is given */
		auto indicate = get_indicate(t);
		filters = std::make_shared<PriorityFilters>(indicate.first, indicate.second);
	}

	driver.install_filters(filters.get());
	const auto tasks_filters
	    = driver.filter_tasks(tasks.get_all_tasks());
	if (tasks_filters.empty()) {
		std::println("No matching result!");
	} else {
		std::println("Result are here: \n{}", TasksListView::format_tasklists_view(tasks_filters));
	}
}
