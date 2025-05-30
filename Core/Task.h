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
	/**
	 * @brief Get the uuid object
	 *
	 * @return const TaskUUID
	 */
	const TaskUUID get_uuid() const noexcept { return uuid; }
	/**
	 * @brief to the printable and displayable format
	 *
	 * @return std::string
	 */
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
		/**
		 * @brief finish build and get the task, invoke this
		 *
		 * @return std::shared_ptr<Task>
		 */
		std::shared_ptr<Task> build_finish();
		/**
		 * @brief Set the ddl object
		 *
		 * @param ddl ddl sets
		 * @return TaskBuilder&
		 */
		TaskBuilder& set_ddl(deadline_raw_t ddl) noexcept;
		/**
		 * @brief Set the description object
		 *
		 * @param desp
		 * @return TaskBuilder&
		 */
		TaskBuilder& set_description(const std::string& desp) noexcept;
		/**
		 * @brief Set the name object
		 *
		 * @param desp
		 * @return TaskBuilder&
		 */
		TaskBuilder& set_name(const std::string& desp) noexcept;
		/**
		 * @brief Set the property object
		 *
		 * @param p
		 * @return TaskBuilder&
		 */
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
