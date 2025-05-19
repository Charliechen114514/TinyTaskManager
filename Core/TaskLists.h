#pragma once
#include "Task.h"
#include "Tools/class_helper.h"
#include <memory>
#include <vector>
class TaskLists {
public:
	TaskLists() = default;
	DISABLE_COPY(TaskLists);

	void enqueue_managing_task(std::shared_ptr<Task> task_en_managed);
	std::vector<std::shared_ptr<Task>> get_all_tasks() const;

private:
	std::vector<std::shared_ptr<Task>> tasklists;
};
