cmake_minimum_required(VERSION 3.10)
project(Audible)

# SDL2 library
#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

# Adding sources
set(SOURCES
    main.cpp
)

# Binary
add_executable(Audible ${SOURCES})

# Link SDL2 library
#target_link_libraries(Audible ${SDL2_LIBRARIES})