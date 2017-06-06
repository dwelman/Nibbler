cmake_minimum_required(VERSION 3.7)
project(nibbler)

set(CMAKE_CXX_STANDARD 11)

include_directories(nibbler includes)

set(SOURCE_FILES 	targsrc/main.cpp
					targsrc/SnakeSegment.cpp
					targsrc/Snake.cpp)


set(INCLUDE_FILES includes/GameManager.hpp
				  includes/Snake.hpp
				  includes/SnakeSegment.hpp)
				  
add_executable(nibbler ${SOURCE_FILES} ${INCLUDE_FILES})