#include "option.h"
#include "Application/application.h"
#include "IO/interative_io/IOFrontEnd.h"

bool CommandOption::sync_option(const CommandOption::OptionHelper& op) {
	StandardShellIO& io = TinyTaskManagerApplication::application_instance().shell_io_instance();
	std::string cmd_line;
	const std::string _title = std::format("{} {} for yes and {} for no\n", op.title, op.ensure_str, op.deny_str);
	while (1) {
		io.write_raw_buffer_to_io(_title);
		TinyTaskManagerApplication::application_instance().display_shell_format();
		io.from_io_raw_buffer(cmd_line);

		if (cmd_line == op.ensure_str) {
			return true;
		} else if (cmd_line == op.deny_str) {
			return false;
		} else {
			io.write_raw_buffer_to_io("invalid option string! retype the session again\n");
		}
	}
}