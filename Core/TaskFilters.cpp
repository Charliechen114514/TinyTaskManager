#include "TaskFilters.h"
namespace {

bool is_satisfied_from_filters(
    const std::shared_ptr<Task>& this_one,
    const std::vector<const AbstractTaskFilters*>& filters) {
	bool passed = true;
	for (const auto& this_filters : filters) {
		passed &= this_filters->is_current_satified(this_one);
	}

	return passed;
}

}; // Tools for compose the filters

std::vector<std::shared_ptr<Task>> TaskFilterDrive::
    filter_tasks(const std::vector<std::shared_ptr<Task>>& original) {

	/* no filters install, so nothing leaves */
	if (filters.empty()) {
		return original;
	}

	std::vector<std::shared_ptr<Task>> result {};
	/* for each filters */
	for (const auto& each_elem : original) {
		if (is_satisfied_from_filters(each_elem, filters)) {
			result.push_back(each_elem);
		}
	}

	return result;
}

bool NameContainsFilter::
    is_current_satified(const std::shared_ptr<Task>& task_handle) const {
	return task_handle->get_task_name().contains(this->keywords);
}

bool PriorityFilters::
    is_current_satified(const std::shared_ptr<Task>& task_handle) const {
	switch (way) {
	case FilterWay::ACCEPT_SAME:
		return task_handle->get_priority() == this->baseline_priority;
	case FilterWay::ACCEPT_HIGH:
		return task_handle->get_priority() > this->baseline_priority;
	case FilterWay::ACCEPT_LOW:
		return task_handle->get_priority() < this->baseline_priority;
	case FilterWay::ACCEPT_SAME_HIGH:
		return task_handle->get_priority() >= this->baseline_priority;
	case FilterWay::ACCEPT_SAME_LOW:
		return task_handle->get_priority() <= this->baseline_priority;
	default:
		return false; // fucking unlikely
	}
}

bool LeavingTimeFilters::
    is_current_satified(const std::shared_ptr<Task>& task_handle) const {
	auto now = std::chrono::system_clock::now();
	auto ddl = task_handle->get_deadline();

	return std::chrono::duration_cast<
	           std::chrono::seconds>(ddl - now) // to seconds level
	    <= leaving_time;
}
