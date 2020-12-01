cmake_minimum_required(VERSION 3.17)
project(workflow)

set(CMAKE_CXX_STANDARD 14)

add_executable(workflow main.cpp workflow.cpp workflow.h Validator.cpp Validator.h ParserFile.cpp ParserFile.h)