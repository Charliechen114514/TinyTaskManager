#include "TaskLists.h"

void TaskLists::
    enqueue_managing_task(std::shared_ptr<Task> task_en_managed) {
	if (task_en_managed) {
		tasklists.push_back(task_en_managed);
	}
}

std::vector<std::shared_ptr<Task>> TaskLists::get_all_tasks() const {
	std::vector<std::shared_ptr<Task>> result;
	result.reserve(tasklists.size());
	for (const auto& uptr : tasklists) {
		result.push_back(uptr);
	}
	return result;
}
