cmake_minimum_required(VERSION 3.7)
project(nibbler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES targsrc/main.cpp)
add_executable(nibbler ${SOURCE_FILES})