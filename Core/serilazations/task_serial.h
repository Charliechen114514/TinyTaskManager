#pragma once
#include "Core/Task.h"

namespace Serializations {

struct AbstractTasksSerializor {
	virtual void save_to(const std::vector<std::shared_ptr<Task>>& saves) = 0;
	virtual std::vector<std::shared_ptr<Task>> load_from() = 0;
	virtual ~AbstractTasksSerializor() = default;
};

struct JsonTasksSerializor : public AbstractTasksSerializor {
private:
	std::string json_path;

public:
	PROPERTY_GET_SET(json_path);
	void save_to(const std::vector<std::shared_ptr<Task>>& saves) override;
	std::vector<std::shared_ptr<Task>> load_from() override;
};

}
