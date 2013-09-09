cmake_minimum_required(VERSION 2.6)
set(PROJECT "solitaire")
project(${PROJECT})

# Include glib
FIND_PACKAGE(GTK2 REQUIRED)

# Compiler definitions
add_definitions(-O2 -pedantic -Wall -Wextra -std=c99)

# Get source
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} SOURCE)

# Set additional include directories
include_directories(${GTK2_INCLUDE_DIRS})

# Add executable
add_executable(${PROJECT} ${SOURCE})
target_link_libraries(${PROJECT} glib-2.0)
target_link_libraries(${PROJECT} m)

# Install
install(TARGETS ${PROJECT} DESTINATION bin)


