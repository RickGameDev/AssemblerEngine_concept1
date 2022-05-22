add_library(ae_window SHARED 
"win32_window.c"
)
target_link_libraries(ae_window PRIVATE AssemblerEngine.API)