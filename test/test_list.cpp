#include "Core/Task.h"
#include "Core/TaskLists.h"
#include <cassert>
#include <iostream>

/**
 * @brief   This test file is expected to make test on the
 *          other apis of tasklists
 *
 */

static constexpr const char* MUST_FIND_NAME = "Flee Happily";

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

	auto task3 = Task::TaskBuilder()
	                 .set_name(MUST_FIND_NAME)
	                 .set_description("Flee out and enjoy life :) ")
	                 .set_ddl(std::chrono::system_clock::now())
	                 .build_finish();

	tasklists.enqueue_managing_task(std::move(task1));
	tasklists.enqueue_managing_task(std::move(task2));
	tasklists.enqueue_managing_task(std::move(task3));

	assert(tasklists.total_size() == 3);

	/* query the tasks with must acceptables */
	auto result = tasklists.query_with_name(MUST_FIND_NAME);
	assert(result.size() == 1);

	/* dumping the result */
	std::cerr << result[0]->toStdString();

	/* removes from managing */
	tasklists.dequeue_managing_task(result[0]);

	/* must success */
	assert(tasklists.total_size() == 2);

	std::cerr << "So the task size now is: " << tasklists.total_size() << "\n";

}
