cmake_minimum_required(VERSION 3.8)
project(tetris)

# Configure compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    # using regular Clang or AppleClang or GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -Wold-style-cast")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    # using Visual Studio C++
    set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

file(COPY assets score.txt DESTINATION ${CMAKE_BINARY_DIR})

set(SOURCE_FILES playfield.cpp tetrominos.cpp game.cpp)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main ${SDL2_LIBRARIES} SDL2_ttf SDL2_image)