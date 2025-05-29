#pragma once
#include <chrono>
/* this is the same as the type: now() returns */
using deadline_raw_t = std::chrono::time_point<
    std::chrono::system_clock,
    std::chrono::nanoseconds>;

enum class TaskPriority {
	/* this is the default */
	LOW = 0,
	MEDIUM = 1,
	HIGH = 2,
	/* this is the highest */
	URGENT = 3
};
static constexpr int TaskPriorityMax = static_cast<int>(TaskPriority::URGENT) + 1;

static constexpr std::array<std::string, TaskPriorityMax> TaskPriorityValues = {
	"LOW", "MEDIUM", "HIGH", "URGENT"
};

static constexpr inline std::string taskPrioirtyString(const TaskPriority p) {
	return TaskPriorityValues.at(static_cast<size_t>(p));
}

#define IS_MATCH(PRIO) \
	(str == TaskPriorityValues[static_cast<size_t>(PRIO)])

static constexpr inline TaskPriority fromTaskPriorityString(const std::string& str) {
	if (IS_MATCH(TaskPriority::LOW))
		return TaskPriority::LOW;
	if (IS_MATCH(TaskPriority::MEDIUM))
		return TaskPriority::MEDIUM;
	if (IS_MATCH(TaskPriority::HIGH))
		return TaskPriority::HIGH;
	if (IS_MATCH(TaskPriority::URGENT))
		return TaskPriority::URGENT;
	return TaskPriority::LOW;
}
