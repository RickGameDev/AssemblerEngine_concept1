add_library(AssemblerEngine STATIC "src/plugin_registry.c" "src/api_registry.c" "src/filesystem.c" "src/hashmap.h" "src/hashmap.c")
target_include_directories(AssemblerEngine PUBLIC "includes" "headers")

add_library(AssemblerEngine_api INTERFACE)
target_include_directories(AssemblerEngine_api INTERFACE "headers")
