/**
 * @file TaskExceptions.h
 * @author Charliechen114514 (chengh1922@mails.jlu.edu.cn)
 * @brief Task Exceptions abstracts
 * @version 0.1
 * @date 2025-05-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include <stdexcept>
/**
 * @brief   BuildException is the exception happens in runtime
 *          Task Build! So, when anycast build exception happens,
 *          We must catch this
 *
 */
class BuildException : public std::runtime_error {
public:
	BuildException()
	    : std::runtime_error("Build Exception") { }
	virtual const char* what() const noexcept {
		return "RunTime Build Exception for some cases...";
	}
};

/**
 * @brief   BuildTaskNameEmpty is the exception happens when
 *          The task name is empty, which should never be empty
 *
 */
class BuildTaskNameEmpty : public BuildException {
public:
	BuildTaskNameEmpty()
	    : BuildException() { }
	virtual const char* what() const noexcept override {
		return "Task Name should never be empty";
	}
};
