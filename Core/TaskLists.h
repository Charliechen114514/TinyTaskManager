// #pragma once
// #include "Task.h"
// #include "Tools/class_helper.h"
// #include <functional>
// #include <memory>
// #include <string>
// #include <unordered_set>
// #include <vector>
// /**
//  * @brief This is a tasklist manager class, in this case, we prefer
//  * to use this for a display/operations sessions
//  *
//  */
// class TaskLists {
// private:
// 	std::string tasklist_name;
// 	std::unordered_set<std::shared_ptr<Task>> tasklists;

// public:
// 	TaskLists() = default;
// 	DISABLE_COPY(TaskLists);
// 	PROPERTY_GET_SET(tasklist_name);
// 	using QueryExpr = std::function<bool(const Task&)>;
// 	/* enqueue and dequeue the managing task */
// 	/* also, we need to add uniquely to prevent the dump add */
// 	void enqueue_managing_task(std::shared_ptr<Task> task_en_managed);
// 	void dequeue_managing_task(std::shared_ptr<Task> task_en_managed);

// 	/* removes the issue */
// 	void enqueue_managing_tasks(std::vector<std::shared_ptr<Task>> tasks);
// 	void dequeue_managing_tasks(std::vector<std::shared_ptr<Task>> tasks);

// 	/**
// 	 * @brief 	query the task by given expressions, which is high level
// 	 *			self defined
// 	 *
// 	 * @param query:	query functions, required to provide how to find
// 	 *					a Task
// 	 * @return std::vector<std::shared_ptr<Task>>
// 	 *		This, as expected, returns a maybe valid Task Handler lists
// 	 *		that is fit the issue
// 	 */
// 	std::vector<std::shared_ptr<Task>>
// 	query(QueryExpr query) const noexcept; /* query, as expected, should never trigger any exceptions */

// 	inline std::vector<std::shared_ptr<Task>>
// 	query_with_name(const std::string& task_name) const noexcept {
// 		return query(
// 		    [&task_name](const Task& iterater) -> bool {
// 			    return iterater.get_task_name() == task_name;
// 		    });
// 	}

// 	/**
// 	 * @brief 	this is expected to return the total size of the task,
// 	 *			with non-privilaged sorted
// 	 *
// 	 * @return size_t return the tasklist without any prority filters
// 	 */
// 	inline size_t total_size() { return tasklists.size(); }

// 	/**
// 	 * @brief Get the all tasks object
// 	 *
// 	 * @return std::vector<std::shared_ptr<Task>> yes, the case :)
// 	 */
// 	std::vector<std::shared_ptr<Task>> get_all_tasks() const;
// };

#pragma once

#include "Task.h"
#include "Tools/class_helper.h"
#include <functional>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

/*	Following only simply provide an issue of make task hashable	*/
struct SharedTaskHash {
	std::size_t operator()(const std::shared_ptr<Task>& t) const {
		return std::hash<std::string>()(t->get_uuid());
	}
};

struct SharedTaskEqual {
	bool operator()(const std::shared_ptr<Task>& a,
	                const std::shared_ptr<Task>& b) const {
		/* force using the equal we defined */
		return *a == *b;
	}
};

class TaskLists {
private:
	std::string tasklist_name;

	/*
	 * well i use this, simply because this can prevent duplicating add
	 */
	using TaskListRawType = std::unordered_set<
	    std::shared_ptr<Task>,
	    SharedTaskHash,
	    SharedTaskEqual>;
	/* ^ Above makes too ill :( */
	TaskListRawType tasklists;

public:
	TaskLists() = default;
	DISABLE_COPY(TaskLists);
	PROPERTY_GET_SET(tasklist_name);

	using QueryExpr = std::function<bool(const Task&)>;

	/**
	 * @brief: enqueue the managing task, makes it enter bunch of Holdings
	 *
	 * @param task_en_managed: The waiting managing the task
	 */
	void enqueue_managing_task(const std::shared_ptr<Task> task_en_managed);

	/**
	 * @brief: dequeue the managing task, makes it leave bunch of Holdings
	 *
	 * @param task_en_managed: The waiting managing the task
	 */
	void dequeue_managing_task(const std::shared_ptr<Task> task_en_managed);

	/**
	 * @brief: enqueue the managing task, makes it enter bunch of Holdings
	 *
	 * @param packs The waiting managing the task
	 */
	void enqueue_managing_tasks(const std::vector<Task::TaskPack>& packs);
	/**
	 * @brief enqueue the managing tasks, makes it enter bunch of Holdings
	 *
	 * @param tasks The waiting managing the task
	 */
	void enqueue_managing_tasks(std::vector<std::shared_ptr<Task>> tasks);
	/**
	 * @brief dequeue the managing tasks, makes it leave bunch of Holdings
	 *
	 * @param tasks The waiting managing the task
	 */
	void dequeue_managing_tasks(std::vector<std::shared_ptr<Task>> tasks);

	/**
	 * @brief query the task by given expressions, which is high level
	 * self defined
	 *
	 * @param query: query functions, required to provide how to find
	 * a Task
	 * @return std::vector<std::shared_ptr<Task>>
	 * This, as expected, returns a maybe valid Task Handler lists
	 * that is fit the issue
	 */
	std::vector<std::shared_ptr<Task>> query(QueryExpr query) const noexcept;

	/**
	 * @brief query the task by given names, which is simply wrapped
	 *
	 * @param task_name: query names, required to provide how to find
	 * a Task
	 * @return std::vector<std::shared_ptr<Task>>
	 * This, as expected, returns a maybe valid Task Handler lists
	 * that is fit the issue
	 */
	inline std::vector<std::shared_ptr<Task>>
	query_with_name(const std::string& task_name) const noexcept {
		return query([&task_name](const Task& t) {
			return t.get_task_name() == task_name;
		});
	}

	/**
	 * @brief this is expected to return the total size of the task,
	 * with non-privilaged sorted
	 *
	 * @return size_t return the tasklist without any prority filters
	 */
	inline size_t total_size() { return tasklists.size(); }

	/**
	 * @brief Get the all tasks object
	 *
	 * @return std::vector<std::shared_ptr<Task>> yes, the case :)
	 */
	std::vector<std::shared_ptr<Task>> get_all_tasks() const;
};
