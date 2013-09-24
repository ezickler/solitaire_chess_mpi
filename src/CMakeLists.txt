cmake_minimum_required(VERSION 2.6)
set(PROJECT "solitaire")
project(${PROJECT})

# Include glib
FIND_PACKAGE(GTK2 REQUIRED)

FIND_PACKAGE(OpenMP) 

if (OPENMP_FOUND)
     set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
     set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}") 
endif()

# Require MPI for this project:
FIND_PACKAGE(MPI REQUIRED)

if (MPI_FOUND)
    set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
    set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
endif()


# Compiler definitions
add_definitions(-O2 -g -pedantic -Wall -Wextra -fopenmp -std=c99)

# Get source
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} SOURCE)

# Set additional include directories
include_directories(${GTK2_INCLUDE_DIRS} MPI_INCLUDE_PATH)

# Add executable
add_executable(${PROJECT} ${SOURCE})
target_link_libraries(${PROJECT} ${MPI_LIBRARIES} glib-2.0)

# Install
install(TARGETS ${PROJECT} DESTINATION bin)


