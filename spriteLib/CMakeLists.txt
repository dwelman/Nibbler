cmake_minimum_required(VERSION 3.7)
project(SpriteRender)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra" )
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE Debug)

include_directories(SpriteRender ~/.brew/include/)

list(APPEND CMAKE_SYSTEM_PREFIX_PATH ~/.brew/lib)

find_path(BREW_LIB ~/.brew/lib)

FIND_LIBRARY(SDL_LIBRARY NAMES SDL2 HINTS ${BREW_LIB})
FIND_LIBRARY(SDL_TTF_LIBRARY NAMES SDL2_ttf HINTS ${BREW_LIB})
FIND_LIBRARY(SDL_IMAGE_LIBRARY NAMES SDL2_image HINTS ${BREW_LIB})
MARK_AS_ADVANCED (SDL_LIBRARY)

SET(EXTRA_LIBS ${SDL_LIBRARY} ${SDL_TTF_LIBRARY} ${SDL_IMAGE_LIBRARY})

set(SOURCE_FILES    targsrc/SpriteLib.cpp
                    targsrc/factory.cpp
                    targsrc/UIElement.cpp
                    targsrc/UIGroup.cpp
                    targsrc/Util.cpp
                    targsrc/mouseEvents.cpp)

set(INCLUDE "./include/")

set(HEADERS ${INCLUDE}SpriteLib.hpp)

include_directories(include ../includes)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})

MESSAGE( STATUS "BASE_DIR: " ${BASE_DIR} )
if (CALLED_FROM_PARENT)
        set(LIBRARY_EXTENSION "dylib")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "lib${PROJECT_NAME}.${LIBRARY_EXTENSION}"
                ${BASE_DIR})

endif()