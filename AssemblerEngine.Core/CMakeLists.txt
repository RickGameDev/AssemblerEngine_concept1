add_library(AssemblerEngine.Core STATIC 
	"src/api_registry.c"
	"src/filesystem.c"
	"src/hashmap.c"
	"src/plugin_registry.c"
)

if(WIN32)
target_sources(AssemblerEngine.Core PRIVATE "src/win32_filesystem.c")
elseif(UNIX)
endif()

target_include_directories(AssemblerEngine.Core PUBLIC "includes")
target_link_libraries(AssemblerEngine.Core PUBLIC AssemblerEngine.API)

if(UNIX)
target_link_libraries(AssemblerEngine.Core PUBLIC ${CMAKE_DL_LIBS})
endif()
