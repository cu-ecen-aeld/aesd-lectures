cmake_minimum_required(VERSION 3.0.0)
project(unity-test)
add_subdirectory(Unity)
include_directories(Unity/src .)
add_executable(unity-test test/Test_time_functions_shared.c test/test_runners/Test_time_functions_shared_Runner.c)
target_link_libraries(unity-test unity)
# See https://cmake.org/cmake/help/latest/command/add_custom_command.html
# Generate our test runner using the auto_generate.sh script
add_custom_target(auto-generate-unity
                   ALL
                   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test/auto_generate.sh
                )
