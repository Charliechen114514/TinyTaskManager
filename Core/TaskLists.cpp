#include "TaskLists.h"

void TaskLists::enqueue_managing_task(const std::shared_ptr<Task> task_en_managed) {
	tasklists.insert(task_en_managed);
}

void TaskLists::dequeue_managing_task(const std::shared_ptr<Task> task_en_managed) {
	tasklists.erase(task_en_managed);
}

void TaskLists::enqueue_managing_tasks(std::vector<std::shared_ptr<Task>> tasks) {
	for (const auto& t : tasks) {
		tasklists.insert(t);
	}
}

void TaskLists::enqueue_managing_tasks(const std::vector<Task::TaskPack>& packs) {

	for (const auto& each_create_session : packs) {
		auto task = Task::TaskBuilder()
		                .set_name(each_create_session.task_name)
		                .set_description(each_create_session.description)
		                .set_ddl(each_create_session.deadline)
		                .set_property(each_create_session.priority)
		                .build_finish();
		tasklists.insert(task);
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
