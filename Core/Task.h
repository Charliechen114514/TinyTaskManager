/**
 * @file Task.h
 * @author Charliechen114514 (chengh1922@mails.jlu.edu.cn)
 * @brief Task Core Defines
 * @version 0.1
 * @date 2025-05-22
 *
 * @copyright Copyright (c) 2025
 *
 */

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
	std::string description {};
	deadline_raw_t deadline {};
	TaskPriority priority {};
	/* Task ID */
	using TaskUUID = std::string;
	const TaskUUID uuid;

public:
	Task(const Task& task);
	/*
	    Oh, I disabled this because uuid must be unique
	 */
	const Task& operator=(const Task&) = delete;

	PROPERTY_GET_SET(task_name);
	PROPERTY_GET_SET(description);
	PROPERTY_GET_SET(deadline);
	PROPERTY_GET_SET(priority);
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
		TaskBuilder& set_property(const TaskPriority p) noexcept;

	private:
		std::shared_ptr<Task> _tmp = std::shared_ptr<Task>(new Task());
	};

	/**
	 * @brief 	TaskPack provides a easy interfaces for one session build,
	 *			This is using for the bunch level create for TaskLists
	 *
	 */
	struct TaskPack {
		std::string task_name {};
		std::string description {};
		deadline_raw_t deadline {};
		TaskPriority priority {};
	};
};
