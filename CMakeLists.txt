cmake_minimum_required(VERSION 3.7)
project(nibbler)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS )
list(APPEND CMAKE_SYSTEM_PREFIX_PATH ~/.brew/lib)

find_path(BREW_LIB ~/.brew/lib)

FIND_LIBRARY(SDL_LIBRARY NAMES SDL2 HINTS ${BREW_LIB})
FIND_LIBRARY(SDL_TTF_LIBRARY NAMES SDL2_ttf HINTS ${BREW_LIB})
MARK_AS_ADVANCED (SDL_LIBRARY)
SET(EXTRA_LIBS ${SDL_LIBRARY} ${SDL_TTF_LIBRARY})

include_directories(nibbler includes ~/.brew/include/)

set(SOURCE_FILES 	targsrc/main.cpp
					targsrc/SnakeSegment.cpp
					targsrc/Snake.cpp
					targsrc/Food.cpp
					targsrc/Entity.cpp
					targsrc/GameManager.cpp
		)


set(INCLUDE_FILES includes/GameManager.hpp
				  includes/Snake.hpp
				  includes/SnakeSegment.hpp
		          includes/Food.hpp
				  includes/Entity.hpp
		)

add_executable(nibbler ${SOURCE_FILES} ${INCLUDE_FILES})

target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})