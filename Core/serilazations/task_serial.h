#pragma once
#include "Core/Task.h"

namespace Serializations {

/**
 * @brief 	AbstractTasksSerializor provides a interface level
 *			serializor
 *
 */
struct AbstractTasksSerializor {
	/**
	 * @brief 	save a bunch of tasks to the serialization mode, in which,
	 *			these leads to a direct save
	 *
	 * @param 	saves the tasks waiting save, should be query from the tasklists
	 */
	virtual void save_to(const std::vector<std::shared_ptr<Task>>& saves) = 0;
	/**
	 * @brief
	 *
	 * @return std::vector<std::shared_ptr<Task>> the task deserailizations
	 * @note 	this can make a exception if parse error occurs, for developers,
	 *			you should use try catch to prevent the terminations of programs
	 */
	virtual std::vector<std::shared_ptr<Task>> load_from() = 0;
	virtual ~AbstractTasksSerializor() = default;
};

struct JsonTasksSerializor : public AbstractTasksSerializor {
private:
	std::string json_path;

public:
	PROPERTY_GET_SET(json_path);
	/**
	 * @brief 	save a bunch of tasks to the serialization mode, in which,
	 *			these leads to a direct save
	 *
	 * @param 	saves the tasks waiting save, should be query from the tasklists
	 */
	void save_to(const std::vector<std::shared_ptr<Task>>& saves) override;
	/**
	 * @brief
	 *
	 * @return std::vector<std::shared_ptr<Task>> the task deserailizations
	 * @note 	this can make a exception if parse error occurs, for developers,
	 *			you should use try catch to prevent the terminations of programs
	 */
	std::vector<std::shared_ptr<Task>> load_from() override;
};

}
