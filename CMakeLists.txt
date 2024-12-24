cmake_minimum_required(VERSION 3.12)

project(main CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

file(GLOB SOURCES 
    src/*.h
    src/*.cpp
    src/commands/*.cpp
    src/commands/*.h
)

add_executable(main.out ${SOURCES})

target_link_libraries(main.out PRIVATE dpp sqlite3)

set_target_properties(main.out PROPERTIES
    CXX_STANDARD 20
)