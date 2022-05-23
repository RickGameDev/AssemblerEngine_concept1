
if (WIN32)
add_library(ae_window SHARED "win32_window.c")
elseif(UNIX)
add_library(ae_window SHARED "linux_window.c")
endif (WIN32)

target_link_libraries(ae_window PRIVATE AssemblerEngine.API)