#include "Core/Task.h"
#include "Core/TaskLists.h"
#include <iostream>

int main() {
	TaskLists tasklists;

	auto task = Task::TaskBuilder()
	                .set_name("Learn Modern C++20")
	                .set_description("My Formal Try in Modern C++")
	                .set_ddl(std::chrono::system_clock::now() + std::chrono::hours(72))
	                .build_finish();

	tasklists.enqueue_managing_task(task);

	for (const auto& t : tasklists.get_all_tasks()) {
		std::cout << "Format Print: \n"
		          << task->toStdString() << "\n";
	}
	return 0;
}