#include "Task.h"
#include "TaskExceptions.h"
#include "Tools/format_time.h"
#include "Tools/uuid_generator.h"
#include <format>
namespace {
bool local_check_name_valid(Task* _task) {
	return !_task->get_task_name().empty();
}

void local_check(Task* _task) {
	if (!local_check_name_valid(_task)) {
		/* Failed the name settings */
		throw BuildTaskNameEmpty();
	}
}

} // namespace

std::shared_ptr<Task> Task::TaskBuilder::build_finish() {
	local_check(this->_tmp.get());
	return std::shared_ptr<Task>(std::move(this->_tmp));
}

Task::TaskBuilder& Task::TaskBuilder::
    set_ddl(deadline_raw_t ddl) noexcept {
	this->_tmp->set_deadline(ddl);
	return *this;
}
Task::TaskBuilder& Task::TaskBuilder::
    set_description(const std::string& desp) noexcept {
	this->_tmp->set_discriptions(desp);
	return *this;
}

Task::TaskBuilder& Task::TaskBuilder::
    set_name(const std::string& desp) noexcept {
	this->_tmp->set_task_name(desp);
	return *this;
}

Task::TaskBuilder& Task::TaskBuilder::
    set_property(const TaskPriority p) noexcept {
	this->_tmp->set_priority(p);
	return *this;
}

Task::Task()
    : uuid(UUIDTools::gen_uuid()) {
}

Task::Task(const Task& task)
    : uuid(UUIDTools::gen_uuid()) {
	this->set_task_name(task.task_name);
	this->set_discriptions(task.discriptions);
	this->set_deadline(task.deadline);
}

std::string Task::toStdString() const noexcept {
	/* at each line, we display the readable strings */
	return std::format("Task Name: {}\nDescription: {}\nDDL: {}\nPriority: {}",
	                   this->get_task_name(),
	                   this->get_discriptions(),
	                   ChronoTools::fromDdlTimeToReadableString(this->get_deadline()),
	                   taskPrioirtyString(this->get_priority()));
}
