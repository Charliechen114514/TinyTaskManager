#pragma once
#include "Core/Task.h"

struct TaskListsSelector {
	std::vector<std::shared_ptr<Task>> init_load();
};
