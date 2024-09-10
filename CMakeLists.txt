# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(nosod VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find and include the spdlog package
find_package(spdlog REQUIRED)

# Add the executable
add_executable(nosod
    nosod.cpp
    application.cpp
)

# Link the spdlog library
target_link_libraries(nosod PRIVATE spdlog::spdlog)
