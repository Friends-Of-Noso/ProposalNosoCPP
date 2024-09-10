cmake_minimum_required(VERSION 3.10)
project(MyApplication)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable target
add_executable(nosod nosod.cpp application.cpp)

# Find and link spdlog
find_package(spdlog REQUIRED)
target_link_libraries(nosod PRIVATE spdlog::spdlog)

# Find and link inih
find_package(PkgConfig REQUIRED)
pkg_check_modules(INIH REQUIRED inih)
include_directories(${INIH_INCLUDE_DIRS})
target_link_libraries(nosod PRIVATE ${INIH_LIBRARIES})