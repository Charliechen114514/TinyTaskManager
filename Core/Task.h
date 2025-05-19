#pragma once
#include "Tools/class_helper.h"
#include "Types.h"
#include <memory>
#include <string>
class Task;

/**
 * @brief  Task is the class that represents a task, which
 *          contains the task name, description, deadline,
 *          and a unique identifier (UUID).
 *
 */
class Task {
private:
	Task();
	std::string task_name {};
	std::string discriptions {};
	deadline_raw_t deadline {};
	/* Task ID */
	using TaskUUID = std::string;
	const TaskUUID uuid;

public:
	PROPERTY_GET_SET(task_name);
	PROPERTY_GET_SET(discriptions);
	PROPERTY_GET_SET(deadline);
	const TaskUUID get_uuid() const noexcept { return uuid; }
	std::string toStdString() const noexcept;
	/* this is the function that helps to check if the task is
	 * equal */
	friend inline bool operator==(const Task& lhs, const Task& rhs) {
		return lhs.get_uuid() == rhs.get_uuid();
	}

	friend class TaskBuilder;
	/**
	 * @brief   TaskBuilder is the class expected to build the
	 *          Task, as a factory
	 *
	 */
	class TaskBuilder {
	public:
		TaskBuilder() = default;
		DISABLE_COPY(TaskBuilder);
		/* when building is finished, call this */
		std::shared_ptr<Task> build_finish();
		/* At any level, only this is expected */
		TaskBuilder& set_ddl(deadline_raw_t ddl) noexcept;
		TaskBuilder& set_description(const std::string& desp) noexcept;
		TaskBuilder& set_name(const std::string& desp) noexcept;

	private:
		std::shared_ptr<Task> _tmp = std::shared_ptr<Task>(new Task());
	};
};
