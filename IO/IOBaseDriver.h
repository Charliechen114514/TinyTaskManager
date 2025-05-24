/**
 * @file IOBaseDriver.h
 * @author Charliechen114514 (chengh1922@mails.jlu.edu.cn)
 * @brief This is the IO Base Driver
 * @version 0.1
 * @date 2025-05-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <string>
struct IOBase {
	/**
	 * @brief   from_io_raw_buffer get the buffer from IO, no matter what the
	 *          IO actually is, thus, concreate IO Driver need to implement the
	 *          how to fetch message from IO, buffer is provided by reference
	 *
	 * @param raw_buffer the buffer contains the result, why raw_buffer is std::string
	 *                   is that the string is expandable and let user decide how to operate
	 */
	virtual void inline from_io_raw_buffer(std::string& raw_buffer) = 0;
	virtual void inline write_raw_buffer_to_io(const std::string& raw_buffer) = 0;
};
