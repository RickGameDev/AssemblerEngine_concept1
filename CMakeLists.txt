# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.21.1)

project ("AssemblerEngine" C)

# Include sub-projects.
add_subdirectory (${CMAKE_PROJECT_NAME}.Core)
add_subdirectory (${CMAKE_PROJECT_NAME})
