cmake_minimum_required(VERSION 3.10)
project(playpauseGet)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIRS})

include_directories(${PULSEAUDIO_INCLUDE_DIRS})

# Adding sources
set(SOURCES
    main.cpp
)

# Binary
add_executable(playpauseGet ${SOURCES})
target_link_libraries(playpauseGet ${X11_LIBRARIES})