cmake_minimum_required(VERSION 3.7)
project(BasicRender)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra" )
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE Debug)

include_directories(BasicRender ~/.brew/include/)

list(APPEND CMAKE_SYSTEM_PREFIX_PATH ~/.brew/lib)

find_path(BREW_LIB ~/.brew/lib)

FIND_LIBRARY(SDL_LIBRARY NAMES SDL2 HINTS ${BREW_LIB})
FIND_LIBRARY(SDL_TTF_LIBRARY NAMES SDL2_ttf HINTS ${BREW_LIB})
MARK_AS_ADVANCED (SDL_LIBRARY)
SET(EXTRA_LIBS ${SDL_LIBRARY} ${SDL_TTF_LIBRARY})

set(SOURCE_FILES    targsrc/NibblerGUI.cpp
                    targsrc/factory.cpp
                    targsrc/UIElement.cpp
                    targsrc/UIGroup.cpp
                    targsrc/Util.cpp
                    targsrc/mouseEvents.cpp)

set(INCLUDE "./include/")


set(HEADERS ${INCLUDE}NibblerGUI.hpp)

include_directories(include ../includes)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})