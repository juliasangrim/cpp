cmake_minimum_required(VERSION 3.17)
project(lab1_tests)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
add_executable(lab1_tests main.cpp tritSet.cpp tritSet.h)
target_link_libraries(lab1_tests gtest gtest_main)