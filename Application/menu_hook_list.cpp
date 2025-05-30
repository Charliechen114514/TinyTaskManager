#include "Application/application.h"
#include "Application/menu_hooks.h"
#include "Core/TaskLists.h"
#include "Core/TaskViews.h"
#include <print>
void MenuActions::process_list(const Command& t) {
	auto tasks = TinyTaskManagerApplication::application_instance().taskLists_instance().get_all_tasks();
	std::print("{}", TasksListView::format_tasklists_view(tasks));
}