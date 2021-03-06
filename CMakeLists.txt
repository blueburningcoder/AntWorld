cmake_minimum_required(VERSION 2.8)
project(AntWorld)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(TGUI 0.6 REQUIRED)

if(NOT SFML_FOUND)
    message(FATAL_ERROR "Could not find SFML")
endif()

if(NOT TGUI_FOUND)
    message(FATAL_ERROR "Could not find TGUI")
endif()

file(GLOB AntWorld_SRC
    "resources/*.*"
    "*.h"
    "*.cpp"
    "*.hpp" )



add_executable(AntWorld main.cpp ${AntWorld_SRC} maze.cpp maze.h GraphicsControl.cpp GraphicsControl.h tile.cpp tile.h ai.cpp ai.h)
target_link_libraries(AntWorld ${TGUI_LIBRARY} ${SFML_LIBRARIES})


# add_dependencies(AntWorld "resources/*.*" )
# add_custom_target(AntWorld "resources/*.*" )


set(EXECUTABLE_NAME "Run_AntWorld2")

