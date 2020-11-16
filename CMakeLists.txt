# CMake Information
cmake_minimum_required(VERSION 2.8)

# Prevent In-Source Builds
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt")
endif()

# Project Information
project(pipe_sim)

# Project Paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Include Information 
include_directories(include)
include_directories(tests)

# Library Sources
file(GLOB LIB_SOURCES "src/*.cpp"
                        "src/instr/*.cpp"
                        "src/memory/*.cpp")

# Application Sources
file(GLOB APP_SOURCES "app/main.cpp")

# Test Sources
file(GLOB TEST_SOURCES "tests/*.cpp"
                        "tests/instr/*.cpp"
                        "tests/memory/*.cpp")

# Library Information
add_library(pipeSimLib ${LIB_SOURCES})

# Executable Information
add_executable(pipeSim ${APP_SOURCES})
target_link_libraries(pipeSim pipeSimLib)

# Testing Information
add_executable(pipeSimTests ${TEST_SOURCES})
target_link_libraries(pipeSimTests pipeSimLib)