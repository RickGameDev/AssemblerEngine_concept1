cmake_minimum_required(VERSION 3.21.1)

project (AssemblerEngine
	VERSION 1.0.0
	LANGUAGES C
	DESCRIPTION "Game engine written in C"
	HOMEPAGE_URL "https://github.com/RickGameDev/AssemblerEngine"
)

# works only for multi-config generators
set ( BUILD_CONFIG $<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>$<$<CONFIG:RelWithdepInfo>:RelWithdepInfo>)
if(NOT BUILD_CONFIG)
    if(NOT CMAKE_BUILD_TYPE)
        set (CMAKE_BUILD_TYPE Release)
    endif(NOT CMAKE_BUILD_TYPE)
    set (BUILD_CONFIG ${CMAKE_BUILD_TYPE})
endif(NOT BUILD_CONFIG)

set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}/${CMAKE_C_COMPILER_ID}/${BUILD_CONFIG}/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)

add_subdirectory (${CMAKE_PROJECT_NAME})