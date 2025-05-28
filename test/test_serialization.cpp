// #include "Core/serilazations/task_serial.h"
// #include <iostream>
// using namespace Serializations;

// int main() {
// 	// 1. Create serializer and set JSON file path
// 	JsonTasksSerializor serializer;
// 	serializer.set_json_path("tasks.json");

// 	// 2. Create sample tasks using TaskBuilder
// 	auto current_time = std::chrono::system_clock::now();

// 	auto task1 = Task::TaskBuilder()
// 	                 .set_name("Complete project report")
// 	                 .set_description("Write final documentation")
// 	                 .set_ddl(current_time + std::chrono::hours(48)) // Due in 2 days
// 	                 .set_property(TaskPriority::HIGH)
// 	                 .build_finish();

// 	auto task2 = Task::TaskBuilder()
// 	                 .set_name("Team meeting")
// 	                 .set_description("Prepare presentation slides")
// 	                 .set_ddl(current_time + std::chrono::hours(24)) // Due tomorrow
// 	                 .set_property(TaskPriority::MEDIUM)
// 	                 .build_finish();

// 	// 3. Store tasks in a vector
// 	std::vector<std::shared_ptr<Task>> tasks = { task1, task2 };

// 	// 4. Save tasks to JSON file
// 	try {
// 		serializer.save_to(tasks);
// 		std::cout << "Tasks saved successfully to " << serializer.get_json_path() << std::endl;
// 	} catch (const std::exception& e) {
// 		std::cerr << "Save failed: " << e.what() << std::endl;
// 		return 1;
// 	}

// 	// 5. Load tasks from JSON file
// 	try {
// 		auto loaded_tasks = serializer.load_from();
// 		std::cout << "\nLoaded tasks (" << loaded_tasks.size() << "):" << std::endl;

// 		for (const auto& task : loaded_tasks) {
// 			std::cout << task->toStdString() << std::endl;
// 		}
// 	} catch (const std::exception& e) {
// 		std::cerr << "Load failed: " << e.what() << std::endl;
// 		return 1;
// 	}

// 	return 0;
// }

#include "Core/serilazations/task_serial.h"
#include <cassert>
#include <chrono>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using namespace Serializations;

// Test constants
static constexpr const char* TEST_JSON_PATH = "test_tasks.json";
static constexpr const char* TEST_TASK1_NAME = "Complete project report";
static constexpr const char* TEST_TASK1_DESC = "Write final documentation";
static constexpr const char* TEST_TASK2_NAME = "Team meeting";
static constexpr const char* TEST_TASK2_DESC = "Prepare presentation slides";

void run_serialization_tests() {
	std::cout << "Running serialization tests...\n";

	// Setup
	JsonTasksSerializor serializer;
	serializer.set_json_path(TEST_JSON_PATH);

	// Clean up any existing test file
	if (fs::exists(TEST_JSON_PATH)) {
		fs::remove(TEST_JSON_PATH);
	}

	// Create test tasks
	auto current_time = std::chrono::system_clock::now();

	auto task1 = Task::TaskBuilder()
	                 .set_name(TEST_TASK1_NAME)
	                 .set_description(TEST_TASK1_DESC)
	                 .set_ddl(current_time + std::chrono::hours(48))
	                 .set_property(TaskPriority::HIGH)
	                 .build_finish();

	auto task2 = Task::TaskBuilder()
	                 .set_name(TEST_TASK2_NAME)
	                 .set_description(TEST_TASK2_DESC)
	                 .set_ddl(current_time + std::chrono::hours(24))
	                 .set_property(TaskPriority::MEDIUM)
	                 .build_finish();

	std::vector<std::shared_ptr<Task>> test_tasks = { task1, task2 };

	// Test 1: Save tasks
	try {
		serializer.save_to(test_tasks);
		std::cout << " [PASS] Save tasks\n";
	} catch (...) {
		std::cout << " [FAIL] Save tasks\n";
		assert(false && "Save tasks failed");
	}
	assert(fs::exists(TEST_JSON_PATH) && "JSON file was not created");

	// Test 2: Load tasks
	std::vector<std::shared_ptr<Task>> loaded_tasks;
	try {
		loaded_tasks = serializer.load_from();
		std::cout << " [PASS] Load tasks\n";
	} catch (...) {
		std::cout << " [FAIL] Load tasks\n";
		assert(false && "Load tasks failed");
	}

	// Test 3: Verify loaded tasks
	assert(loaded_tasks.size() == test_tasks.size() && "Number of loaded tasks doesn't match saved tasks");

	assert(loaded_tasks[0]->get_task_name() == TEST_TASK1_NAME && "Task1 name mismatch");
	assert(loaded_tasks[0]->get_description() == TEST_TASK1_DESC && "Task1 description mismatch");
	assert(loaded_tasks[0]->get_priority() == TaskPriority::HIGH && "Task1 priority mismatch");

	assert(loaded_tasks[1]->get_task_name() == TEST_TASK2_NAME && "Task2 name mismatch");
	assert(loaded_tasks[1]->get_description() == TEST_TASK2_DESC && "Task2 description mismatch");
	assert(loaded_tasks[1]->get_priority() == TaskPriority::MEDIUM && "Task2 priority mismatch");

	// Test 4: Load non-existent file
	fs::remove(TEST_JSON_PATH);
	bool load_failed = false;
	try {
		auto should_fail = serializer.load_from();
	} catch (...) {
		load_failed = true;
	}
	assert(load_failed && "Should throw when loading non-existent file");
	std::cout << " [PASS] Non-existent file handling\n";

	// Test 5: Save empty vector
	std::vector<std::shared_ptr<Task>> empty_tasks;
	try {
		serializer.save_to(empty_tasks);
		std::cout << " [PASS] Save empty vector\n";
	} catch (...) {
		std::cout << " [FAIL] Save empty vector\n";
		assert(false && "Save empty vector failed");
	}

	auto empty_loaded = serializer.load_from();
	assert(empty_loaded.empty() && "Loaded empty vector should be empty");

	// Cleanup
	if (fs::exists(TEST_JSON_PATH)) {
		fs::remove(TEST_JSON_PATH);
	}

	std::cout << "All tests passed successfully!\n";
}

int main() {
	run_serialization_tests();
	return 0;
}