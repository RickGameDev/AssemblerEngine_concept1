add_executable(AssemblerEngine "src/main.c" )

target_link_libraries(AssemblerEngine PRIVATE AssemblerEngine.Core)
add_dependencies(AssemblerEngine ae_camera ae_imgui ae_logging ae_opengl_backend ae_window)