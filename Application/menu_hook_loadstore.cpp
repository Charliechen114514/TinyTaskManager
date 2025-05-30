#include "Application/application.h"
#include "Application/menu_hooks.h"
#include "Application/option.h"
#include "Core/TaskExceptions.h"
#include "Core/TaskLists.h"
#include "Core/serilazations/task_serial.h"
#include "IO/file_io/fileio.h"
#include "IO/interative_io/IOFrontEnd.h"
#include <filesystem>
#include <print>
namespace {

void load_pass_checks(const std::filesystem::path& p) {
	if (!FileIOTools::is_file_exsited(p)) {
		throw LoadException(p, "file is not exsited");
	}

	if (!FileIOTools::is_readable(p)) {
		throw LoadException(p, "file is unreadable!");
	}
}

void store_pass_checks(const std::filesystem::path& p) {
	if (!FileIOTools::is_writable(p)) {
		throw StoreException(p, "file is unreadable!");
	}
}

std::filesystem::path sync_query_load_from_cmdline() {
	std::string cmd;
	std::filesystem::path result;
	StandardShellIO& io = TinyTaskManagerApplication::application_instance().shell_io_instance();
loop_again:
	while (1) {
		std::println("Submit a parsable path to the task json file");
		TinyTaskManagerApplication::application_instance().display_shell_format();
		io.from_io_raw_buffer(cmd);
		result = { cmd };
		try {
			load_pass_checks(result);
			break;
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			continue;
		}
	}

	/* query for the ensure */
	bool op = CommandOption::sync_option(
	    { std::format("Are you sure the file: {}?", FileIOTools::to_abs_Path(result).string()),
	      "y",
	      "n",
	      "ensure the load file!" });

	if (!op) {
		std::println("Then do it again!");
		goto loop_again;
	}

	return result;
}

std::filesystem::path sync_query_store_from_cmdline() {
	std::string cmd;
	std::filesystem::path result;
	StandardShellIO& io = TinyTaskManagerApplication::application_instance().shell_io_instance();
loop_again:
	while (1) {
		std::println("Submit a parsable path to the save as a task json file");
		TinyTaskManagerApplication::application_instance().display_shell_format();
		io.from_io_raw_buffer(cmd);
		result = { cmd };
		try {
			store_pass_checks(result);
			break;
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			continue;
		}
	}

	/* query for the ensure */
	bool op = CommandOption::sync_option(
	    { std::format("Are you sure write to the location: {}?", FileIOTools::to_abs_Path(result).string()),
	      "y",
	      "n",
	      "ensure the save file!" });

	if (!op) {
		std::println("Then do it again!");
		goto loop_again;
	}

	return result;
}

}

void MenuActions::process_load(const Command& t) {
	std::filesystem::path json_path;
	if (t.args.size() == 1) {
		/* then use the default command indications */
		try {
			load_pass_checks(t.args[0]);
			json_path = t.args[0];
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			/* then jump to the sync issue */
			json_path = sync_query_load_from_cmdline();
		}
	} else if (t.args.empty()) {
		json_path = sync_query_load_from_cmdline();
	} else {
		throw argument_count_mismatch();
	}

	Serializations::JsonTasksSerializor serilazations;
	serilazations.set_json_path(json_path);
	try {
		auto result = serilazations.load_from();
		TinyTaskManagerApplication::application_instance()
		    .taskLists_instance()
		    .enqueue_managing_tasks(result);
		std::println("Finish the load! You can type list to see the table!");
	} catch (const std::exception& e) {
		// oh, parse error
		std::cout << e.what() << std::endl;
		std::println("Error for the trying format! check the file you load!");
	}
}

void MenuActions::process_store(const Command& t) {
	std::filesystem::path json_path;
	if (t.args.size() == 1) {
		/* then use the default command indications */
		try {
			store_pass_checks(t.args[0]);
			json_path = t.args[0];
		} catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			/* then jump to the sync issue */
			json_path = sync_query_store_from_cmdline();
		}
	} else if (t.args.empty()) {
		json_path = sync_query_store_from_cmdline();
	} else {
		throw argument_count_mismatch();
	}

	Serializations::JsonTasksSerializor serilazations;
	serilazations.set_json_path(json_path);
	try {
		auto tasks = TinyTaskManagerApplication::application_instance()
		                 .taskLists_instance()
		                 .get_all_tasks();
		serilazations.save_to(tasks);
		std::println("Finish store!You can see {} for details!", FileIOTools::to_abs_Path(json_path).string());
	} catch (const std::exception& e) {
		// oh, parse error
		std::cout << e.what() << std::endl;
		std::println("Error for the trying format! check the file you load!");
	}
}