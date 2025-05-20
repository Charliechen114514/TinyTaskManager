#pragma once
#include "TaskLists.h"
/**
 * @brief TaskViews Only make a
    simple jobs on how to display a TaskLists with given
    Views, required only
 *
 */
class TasksListView {
public:
	/* Dangling View is never acceptable */
	TasksListView() = delete;
	DISABLE_COPY(TasksListView);
	static constexpr std::array<std::string, 4> headers = {
		"Name", "Description", "Deadline",
		"Priority"
	};

	enum COL_INDEX {
		NAME,
		DESP,
		DDL,
		PRIORITY
	};

	/**
	 * @brief format_tasklists_view makes a default actions
	 *
	 * @param l: l indicates the sorted sequence of tasks
	 * @return std::string: the format string waiting for direct display
	 */
	static std::string format_tasklists_view(
	    const std::vector<std::shared_ptr<Task>>& l);
	/* You tells how to format  */
	/**
	 * @brief format_tasklists_view makes a default actions
	 *
	 * @param l l indicates the sorted sequence of tasks
	 * @param f for developers, of you wanna define your own printer
	 *          just provide functions you like
	 * @return std::string
	 */
	static std::string format_tasklists_view(
	    const std::vector<std::shared_ptr<Task>>& l,
	    std::function<std::string(const std::vector<std::shared_ptr<Task>>& l)> f);
};
