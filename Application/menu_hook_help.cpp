#include "Application/application.h"
#include "Application/help_helper.h"
#include "Application/menu_hooks.h"
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