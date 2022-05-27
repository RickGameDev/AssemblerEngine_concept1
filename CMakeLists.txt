cmake_minimum_required(VERSION 3.21.1)

project (AssemblerEngine
	VERSION 1.0.0
	LANGUAGES C
	DESCRIPTION "plugin engine written in C"
	HOMEPAGE_URL "https://github.com/RickGameDev/AssemblerEngine"
)

set (CMAKE_C_STANDARD 11)

#option(BUILD_DOC "Build documentation" ON)

# works only for multi-config generators
#set ( BUILD_CONFIG $<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>$<$<CONFIG:RelWithdepInfo>:RelWithdepInfo>)
#
#if(NOT BUILD_CONFIG)
#    if(NOT CMAKE_BUILD_TYPE)
#        set (CMAKE_BUILD_TYPE Release)
#    endif(NOT CMAKE_BUILD_TYPE)
#    set (BUILD_CONFIG ${CMAKE_BUILD_TYPE})
#endif(NOT BUILD_CONFIG)
#
#set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}/${CMAKE_C_COMPILER_ID}/${BUILD_CONFIG}/)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

# needed for linux
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
	add_definitions("-D_Float128=__float128")
endif()

add_subdirectory (AssemblerEngine.API)
add_subdirectory (AssemblerEngine.Plugins)
add_subdirectory (AssemblerEngine.Core)
add_subdirectory (AssemblerEngine)

include("docs/DoxyGen.cmake")