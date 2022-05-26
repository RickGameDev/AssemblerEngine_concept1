cmake_minimum_required(VERSION 3.21.1)

project (AssemblerEngine
	VERSION 1.0.0
	LANGUAGES C
	DESCRIPTION "plugin engine written in C"
	HOMEPAGE_URL "https://github.com/RickGameDev/AssemblerEngine"
)

#option(BUILD_DOC "Build documentation" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory (AssemblerEngine.API)
add_subdirectory (AssemblerEngine.Plugins)
add_subdirectory (AssemblerEngine.Core)
add_subdirectory (AssemblerEngine)

include("docs/DoxyGen.cmake")