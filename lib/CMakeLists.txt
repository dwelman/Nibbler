cmake_minimum_required(VERSION 3.7)
project(SpriteRender)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra" )
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE Debug)

IF(APPLE)
    FIND_LIBRARY(SDL_LIBRARY SDL2 )
    MARK_AS_ADVANCED (SDL_LIBRARY)
    SET(EXTRA_LIBS ${SDL_LIBRARY})
ENDIF (APPLE)

set(SOURCE_FILES NibblerGUI.cpp factory.cpp)
set(INCLUDE "./")
set(HEADERS ${INCLUDE}NibblerGUI.hpp)

include_directories(includes .)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})