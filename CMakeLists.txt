cmake_minimum_required(VERSION 3.7)
project(nibbler)

set(CMAKE_CXX_STANDARD 11)


IF(APPLE)
	FIND_LIBRARY(SDL_LIBRARY SDL2 )
	MARK_AS_ADVANCED (SDL_LIBRARY)
	SET(EXTRA_LIBS ${SDL_LIBRARY})
ENDIF (APPLE)


include_directories(nibbler includes)

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