add_executable(test_runner test_normal.cpp)

target_link_libraries(test_runner PRIVATE tasklib)
enable_testing()
add_test(NAME RunTaskTests COMMAND test_runner)
