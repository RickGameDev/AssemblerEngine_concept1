cmake_minimum_required(VERSION 3.21.1)

project (AssemblerEngine
	VERSION 1.0.0
	LANGUAGES C
	DESCRIPTION "plugin engine written in C"
	HOMEPAGE_URL "https://github.com/RickGameDev/AssemblerEngine"
)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

add_subdirectory (AssemblerEngine.API)
add_subdirectory (AssemblerEngine.Plugins)
add_subdirectory (AssemblerEngine.Core)
add_subdirectory (AssemblerEngine)