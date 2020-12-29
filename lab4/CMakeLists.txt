cmake_minimum_required(VERSION 3.17)
project(csv)

set(CMAKE_CXX_STANDARD 17)

add_executable(csv main.cpp printTuple.h CSVParser.h ParserException.cpp ParserException.h)