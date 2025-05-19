// test/test_tasklist.cpp
#include "Core/Task.h"
#include "Core/TaskExceptions.h"
#include "Core/TaskLists.h"
#include <cassert>
#include <iostream>

int main() {
	TaskLists tasklists;

	auto task1 = Task::TaskBuilder()
	                 .set_name("Clean Room")
	                 .set_description("Vacuum and mop the entire floor.")
	                 .set_ddl(std::chrono::system_clock::now() + std::chrono::hours(48))
	                 .build_finish();

	auto task2 = Task::TaskBuilder()
	                 .set_name("Write Report")
	                 .set_description("Summarize project findings and conclusions.")
	                 .set_ddl(std::chrono::system_clock::now() + std::chrono::hours(72))
	                 .build_finish();

	tasklists.enqueue_managing_task(std::move(task1));
	tasklists.enqueue_managing_task(std::move(task2));

	auto all_tasks = tasklists.get_all_tasks();
	assert(all_tasks.size() == 2 && "Error in task list size");

	assert(all_tasks[0] != all_tasks[1] && "UUID is not unique");

	/* test if we can correct catch the name empty exceptions */
	bool excepted_res = false;
	try {
		auto task3 = Task::TaskBuilder()
		                 .set_name("")
		                 .set_description("This should throw an exception.")
		                 .set_ddl(std::chrono::system_clock::now())
		                 .build_finish();
	} catch (const BuildTaskNameEmpty& e) {
		excepted_res = true;
		std::cout << "Caught expected exception: " << e.what() << std::endl;
	}

	assert(excepted_res && "not catch the exception");

	return 0;
}
