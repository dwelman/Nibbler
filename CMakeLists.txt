cmake_minimum_required(VERSION 3.7)
project(nibbler)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wno-unused-variable -Wno-unused-parameter")

include_directories(nibbler includes)

set(SOURCE_FILES 	targsrc/main.cpp
					targsrc/SnakeSegment.cpp
					targsrc/Snake.cpp
					targsrc/Food.cpp)


set(INCLUDE_FILES includes/GameManager.hpp
				  includes/Snake.hpp
				  includes/SnakeSegment.hpp
		          includes/Food.hpp)
				  
add_executable(nibbler ${SOURCE_FILES} ${INCLUDE_FILES})