add_executable(basic_show basic_show.cpp)
target_link_libraries(basic_show PRIVATE tasklib)

add_executable(basic_filters basic_filters.cpp)
target_link_libraries(basic_filters PRIVATE tasklib)