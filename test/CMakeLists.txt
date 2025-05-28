function(add_test_executable test_name source_file)
    add_executable(${test_name} ${source_file})
    target_link_libraries(${test_name} PRIVATE tasklib)
    add_test(NAME Run${test_name}Tests COMMAND ${test_name})
endfunction()

enable_testing()

add_test_executable(test_runner test_normal.cpp)
add_test_executable(test_runner2 test_list.cpp)
add_test_executable(test_baseio test_baseio.cpp)
add_test_executable(test_parser test_parse.cpp)
add_test_executable(test_serialization test_serialization.cpp)