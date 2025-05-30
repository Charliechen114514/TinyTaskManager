/**
 * @file TaskFilters.h
 * @author Charliechen114514 (chengh1922@mails.jlu.edu.cn)
 * @brief Files implement the task filters, which is used to filter
 *        the tasklists show, that means
 *        1. one should query from the physical tasklists
 *        2. from the tasklists, we get the raw tasks
 *        3. we filter the tasks by the filters
 *        4. we show the filtered tasks by sending it to TaskListsView
 * @version 0.1
 * @date 2025-05-22
 * @note    I Know the std::ranges and std::view sessions,
 *          but I decided to make an own by myself
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include "Task.h"

/**
 * @brief   AbstractTaskFilters defines
 *
 */
struct AbstractTaskFilters {
public:
	AbstractTaskFilters() = default;
	virtual ~AbstractTaskFilters() = default;
	/**
	 * @brief one must implement the interfaces,
	    if the current tasks really satisfied, then one should return true
	    else return false
	 *
	 * @param task_handle
	 * @return if the task_handle can pass the filters
	 */
	virtual bool is_current_satified(const std::shared_ptr<Task>& task_handle) const = 0;
};

/**
 * @brief TaskFilterDrive collects the filters and make drive
 *
 */
struct TaskFilterDrive {
private:
	std::vector<const AbstractTaskFilters*> filters {};

public:
	/**
	 * @brief install_filters install a filters into the drivers
	 *
	 * @param f filters append
	 */
	inline TaskFilterDrive& install_filters(const AbstractTaskFilters* f) {
		filters.push_back(f);
		return *this;
	}

	/**
	 * @brief remove_filters remove the filters from the drivers
	 *
	 * @param f filters remove
	 */
	inline TaskFilterDrive& remove_filters(const AbstractTaskFilters* f) {
		auto result = std::remove(filters.begin(), filters.end(), f);
		/* then things exsited */
		if (result != filters.end()) {
			filters.erase(result, filters.end());
		}
		return *this;
	}

	/**
	 * @brief filter_tasks filter the tasks by the filters
	 *
	 * @param tasks the tasks to be filtered, this will filters the variables
	 * you pass
	 * @return std::vector<std::shared_ptr<Task>> the filtered tasks
	 */
	std::vector<std::shared_ptr<Task>> filter_tasks(const std::vector<std::shared_ptr<Task>>& original);
};

/**
 * @brief   NameContainsFilter provides the common name
 *          filters
 *
 */
struct NameContainsFilter : public AbstractTaskFilters {
	/**
	 * @brief   keywords for the filters, if the
	 *          tasks name contains the keywords, then we filters pass
	 */
	const std::string keywords;
	NameContainsFilter() = delete;

	/* Build Time Specify the keywords */
	NameContainsFilter(const std::string& k)
	    : keywords(k) { }

	virtual bool is_current_satified(const std::shared_ptr<Task>& task_handle) const override;
};

/**
 * @brief 	Priority Filters checks here, these will decide which
 *			tasks can pass the filters
 *
 */
struct PriorityFilters : public AbstractTaskFilters {
	enum class FilterWay {
		ACCEPT_HIGH,
		ACCEPT_LOW,
		ACCEPT_SAME,
		ACCEPT_SAME_HIGH,
		ACCEPT_SAME_LOW
	};
	const TaskPriority baseline_priority;
	const FilterWay way;

	PriorityFilters() = delete;

	PriorityFilters(const TaskPriority base, const FilterWay way)
	    : baseline_priority(base)
	    , way(way) { }

	virtual bool is_current_satified(const std::shared_ptr<Task>& task_handle) const override;
};

struct LeavingTimeFilters : public AbstractTaskFilters {
	/* this is the time we leave */
	const std::chrono::seconds leaving_time;
	LeavingTimeFilters() = delete;

	LeavingTimeFilters(const std::chrono::seconds leaving_time)
	    : leaving_time(leaving_time) { }

	virtual bool is_current_satified(const std::shared_ptr<Task>& task_handle) const override;
};
