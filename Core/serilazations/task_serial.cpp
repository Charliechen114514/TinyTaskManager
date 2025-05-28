#include "task_serial.h"
#include <fstream>
#include <third_party/json.hpp>
using nlohmann::json;
namespace nlohmann {
template <>
struct adl_serializer<deadline_raw_t> {
	static void to_json(json& j, const deadline_raw_t& ddl) {
		auto ns = ddl.time_since_epoch().count();
		j = ns;
	}

	static void from_json(const json& j, deadline_raw_t& ddl) {
		auto ns = j.get<long long>();
		ddl = deadline_raw_t { std::chrono::nanoseconds { ns } };
	}
};

template <>
struct adl_serializer<std::shared_ptr<Task>> {
	static void to_json(json& j, const std::shared_ptr<Task>& t) {
		j = json {
			{ "task_name", t->get_task_name() },
			{ "description", t->get_description() },
			{ "deadline", t->get_deadline() },
			{ "priority", t->get_priority() }
		};
	}

	static void from_json(const json& j, std::shared_ptr<Task>& t) {
		t = Task::TaskBuilder()
		        .set_name(j.at("task_name").get<std::string>())
		        .set_description(j.at("description").get<std::string>())
		        .set_ddl(j.at("deadline").get<deadline_raw_t>())
		        .set_property(j.at("priority").get<TaskPriority>())
		        .build_finish();
	}
};
}

void Serializations::JsonTasksSerializor::
    save_to(const std::vector<std::shared_ptr<Task>>& saves) {
	json j = saves;
	std::ofstream(json_path) << std::setw(4) << j;
}

std::vector<std::shared_ptr<Task>>
Serializations::JsonTasksSerializor::load_from() {
	std::ifstream ifs(json_path);
	json j;
	ifs >> j;
	return j.get<std::vector<std::shared_ptr<Task>>>();
}