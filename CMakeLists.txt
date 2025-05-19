cmake_minimum_required(VERSION 3.10.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(TaskManager VERSION 0.1.0 LANGUAGES C CXX)

message(STATUS "Time Checking issues!")
if(DEFINED ENV{TZ})
  set(SYSTEM_TIMEZONE $ENV{TZ})
elseif(EXISTS "/etc/timezone")
    file(READ "/etc/timezone" SYSTEM_TIMEZONE)
    string(STRIP "${SYSTEM_TIMEZONE}" SYSTEM_TIMEZONE)
else()
    message(WARNING "No timezone information found. Defaulting to UTC.")
    set(SYSTEM_TIMEZONE "UTC")
endif()
message(STATUS "System Timezone: ${SYSTEM_TIMEZONE}")

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/configures/timezone.h.in"
  "${CMAKE_BINARY_DIR}/timezone.h"
  @ONLY
)

set(CoreSrc 
    Core/Task.cpp
    Core/Task.h
    Core/TaskLists.h
    Core/TaskLists.cpp)

set(ToolsSrc
    Tools/class_helper.h
    Tools/format_time.h
    Tools/format_time.cpp
    Tools/uuid_generator.h
    Tools/uuid_generator.cpp)

add_library(tasklib STATIC ${CoreSrc} ${ToolsSrc})
add_executable(TaskManager main.cpp)
target_link_libraries(TaskManager PRIVATE tasklib)
target_include_directories(tasklib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR})
add_subdirectory(test)
