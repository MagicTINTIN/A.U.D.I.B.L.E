cmake_minimum_required(VERSION 3.10)
project(srvMsg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

# Find Boost
find_package(Boost 1.70 REQUIRED COMPONENTS system)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found. Please install Boost.")
endif()

# Adding sources
set(SOURCES
    main.cpp
)

# Binary
add_executable(srvMsg ${SOURCES})
# Link Boost libraries
target_link_libraries(srvMsg Boost::system)