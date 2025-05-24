/**
 * @file uuid_generator.h
 * @author Charliechen114514 (chengh1922@mails.jlu.edu.cn)
 * @brief This file provides the UUID generator, which is used to
 *        generate a unique identifier for each task.
 * @version 0.1
 * @date 2025-05-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <string>

namespace UUIDTools {
/**
 * @brief   This is a function that helps to generate the UUID
 *          for the task, as a string
 *
 * @return std::string the generated UUID
 */
std::string gen_uuid();
}
