#include "Core/Task.h"
#include "Core/TaskLists.h"
#include "Core/TaskViews.h"
#include <iostream>

int main() {
	TaskLists tasklists;

	auto task = Task::TaskBuilder()
	                .set_name("Learn Modern C++20")
	                .set_description("My Formal Try in Modern C++")
	                .set_ddl(std::chrono::system_clock::now() + std::chrono::hours(72))
	                .set_property(TaskPriority::HIGH)
	                .build_finish();

	tasklists.enqueue_managing_task(task);

	auto task2 = Task::TaskBuilder()
	                 .set_name("Learn CMake")
	                 .set_description("Attempt to make sense with CMake")
	                 .set_ddl(std::chrono::system_clock::now() + std::chrono::hours(72))
	                 .set_property(TaskPriority::MEDIUM)
	                 .build_finish();

	tasklists.enqueue_managing_task(task2);
	std::cout << TasksListView::format_tasklists_view(tasklists.get_all_tasks());
	return 0;
}