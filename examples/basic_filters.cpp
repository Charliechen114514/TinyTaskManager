/**
 * @file basic_filters.cpp
 * @author Charliechen114514 (chengh1922@mails.jlu.edu.cn)
 * @brief this file show the basic filters usage
 * @version 0.1
 * @date 2025-05-22
 *
 *
 */

#include "Core/Task.h"
#include "Core/TaskFilters.h"
#include "Core/TaskLists.h"
#include "Core/TaskViews.h"
#include <iostream>

int main() {
	TaskLists tasklists;

	std::vector<Task::TaskPack> example_task_pack = {
		{ .task_name = "Learn Modern C++20",
		  .discriptions = "My Formal Try in Modern C++",
		  .deadline = std::chrono::system_clock::now() + std::chrono::hours(72),
		  .priority = TaskPriority::HIGH },
		{ .task_name = "Learn CMake",
		  .discriptions = "Attempt to make sense with CMake",
		  .deadline = std::chrono::system_clock::now() + std::chrono::hours(72),
		  .priority = TaskPriority::MEDIUM },
		{ .task_name = "Read C++20 Standard",
		  .discriptions = "Deep dive into the latest C++20 features.",
		  .deadline = std::chrono::system_clock::now() + std::chrono::hours(96),
		  .priority = TaskPriority::HIGH },
		{ .task_name = "Write Project Documentation",
		  .discriptions = "Document the architecture and usage of the TaskManager.",
		  .deadline = std::chrono::system_clock::now() + std::chrono::hours(120),
		  .priority = TaskPriority::MEDIUM },
		{ .task_name = "Optimize Performance",
		  .discriptions = "Profile and optimize the TaskManager for better efficiency.",
		  .deadline = std::chrono::system_clock::now() + std::chrono::hours(72),
		  .priority = TaskPriority::HIGH },
		{ .task_name = "Write Unit Tests",
		  .discriptions = "Ensure all components are properly tested.",
		  .deadline = std::chrono::system_clock::now() + std::chrono::hours(48),
		  .priority = TaskPriority::MEDIUM },
		{ .task_name = "Prepare Release Version",
		  .discriptions = "Finalize and package the TaskManager for release.",
		  .deadline = std::chrono::system_clock::now() + std::chrono::hours(168),
		  .priority = TaskPriority::LOW },
		{ .task_name = "Code Review",
		  .discriptions = "Review code submissions for quality and consistency.",
		  .deadline = std::chrono::system_clock::now() + std::chrono::hours(36),
		  .priority = TaskPriority::MEDIUM },
		{ .task_name = "Team Meeting",
		  .discriptions = "Discuss project milestones and remaining tasks.",
		  .deadline = std::chrono::system_clock::now() + std::chrono::hours(24),
		  .priority = TaskPriority::LOW },
		{ .task_name = "Refactor TaskManager Core",
		  .discriptions = "Improve code structure and remove redundancies.",
		  .deadline = std::chrono::system_clock::now() + std::chrono::hours(60),
		  .priority = TaskPriority::HIGH }
	};

	tasklists.enqueue_managing_tasks(example_task_pack);

	std::cout << TasksListView::format_tasklists_view(tasklists.get_all_tasks());
	/* filter the tasks */
	NameContainsFilter filters("R");
	TaskFilterDrive drive;
	PriorityFilters filters2(TaskPriority::MEDIUM, PriorityFilters::FilterWay::ACCEPT_SAME_HIGH);
	drive.install_filters(&filters).install_filters(&filters2);

	auto result = drive.filter_tasks(tasklists.get_all_tasks());

	std::cout << "After Filters\n";
	std::cout << TasksListView::format_tasklists_view(result);

	return 0;
}