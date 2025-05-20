#include "TaskLists.h"

void TaskLists::enqueue_managing_task(std::shared_ptr<Task> task_en_managed) {
	tasklists.insert(task_en_managed);
}

void TaskLists::dequeue_managing_task(std::shared_ptr<Task> task_en_managed) {
	tasklists.erase(task_en_managed);
}

void TaskLists::enqueue_managing_tasks(std::vector<std::shared_ptr<Task>> tasks) {
	for (const auto& t : tasks) {
		tasklists.insert(t);
	}
}

void TaskLists::dequeue_managing_tasks(std::vector<std::shared_ptr<Task>> tasks) {
	for (const auto& t : tasks) {
		tasklists.erase(t);
	}
}

std::vector<std::shared_ptr<Task>> TaskLists::get_all_tasks() const {
	std::vector<std::shared_ptr<Task>> result;
	/* reserved, as this can prevent multi-times malloc */
	result.reserve(tasklists.size());
	for (const auto& task : tasklists) {
		result.push_back(task);
	}
	return result;
}

std::vector<std::shared_ptr<Task>>
TaskLists::query(TaskLists::QueryExpr query) const noexcept {
	std::vector<std::shared_ptr<Task>> result;
	for (const auto& task : tasklists) {
		if (query(*task)) {
			result.push_back(task);
		}
	}
	return result;
}
