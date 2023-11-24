# mkdir build <- makes the build directory
# cmake .. 
# make

find_package(Eigen3 REQUIRED)

# Set the compiler
if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER "/usr/bin/g++")
endif()

# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(quadruped)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the build type to Debug - Needs to be here for debugging (change to release when done)
set(CMAKE_BUILD_TYPE release)

# Add source files to the project
set(SOURCES
    src/components.cpp
    src/gait.cpp
    src/optimization.cpp
)

# Include Directories
include_directories(include)
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})

# Add executable target
add_executable(main main.cpp ${SOURCES})