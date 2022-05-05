add_library(${CMAKE_PROJECT_NAME} STATIC "src/plugin_registry.c" "src/api_registry.c" "src/filesystem.c")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "includes" "headers")

add_library(${CMAKE_PROJECT_NAME}_api INTERFACE)
target_include_directories(${CMAKE_PROJECT_NAME}_api INTERFACE "headers")
