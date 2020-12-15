cmake_minimum_required(VERSION 3.17)
project(SeaBattle)

set(CMAKE_CXX_STANDARD 14)
add_executable(SeaBattle main.cpp Gamer.cpp Gamer.h GameView.cpp GameView.h parser.cpp parser.h Game.cpp Game.h)