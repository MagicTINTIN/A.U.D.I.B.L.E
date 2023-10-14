cmake_minimum_required(VERSION 3.10)
project(Audible)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

# Find Boost
find_package(Boost 1.70 REQUIRED COMPONENTS system)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found. Please install Boost.")
endif()

set(CMAKE_CXX_STANDARD 11)
find_path(PULSEAUDIO_INCLUDE_DIR
        NAMES pulse/pulseaudio.h
        DOC "The PulseAudio include directory"
        )
find_library(PULSEAUDIO_LIBRARY
        NAMES pulse
        DOC "The PulseAudio library"
        )

include_directories(${PULSEAUDIO_INCLUDE_DIRS})

# Adding sources
set(SOURCES
    main.cpp
)

# Binary
add_executable(Audible ${SOURCES})
# Link Boost libraries
target_link_libraries(Audible Boost::system)
# link pulse audio
target_link_libraries(Audible pulse-simple pulse)