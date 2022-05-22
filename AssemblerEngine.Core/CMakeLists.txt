add_library(AssemblerEngine.Core STATIC 
	"src/api_registry.c"
	"src/filesystem.c"
	"src/hashmap.c"
	"src/plugin_registry.c"
	 
	"src/win32_vm_allocator.c" 
	"src/win32_system_info.c" )

target_include_directories(AssemblerEngine.Core PUBLIC "includes")
target_link_libraries(AssemblerEngine.Core PUBLIC AssemblerEngine.API)
