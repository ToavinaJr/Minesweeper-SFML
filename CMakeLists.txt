cmake_minimum_required(VERSION 3.16)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "source/*.cpp")

# Create executable
add_executable(Minesweeper ${SOURCES})

# Link SFML libraries
target_link_libraries(Minesweeper sfml-graphics sfml-window sfml-system)

# Copy assets to build directory
add_custom_command(TARGET Minesweeper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)
