add_library(ae_opengl_backend SHARED 
"win32_opengl_backend.c" 
"glad.c"
"opengl_shader.c"
"opengl_renderer.c")
target_link_libraries(ae_opengl_backend PRIVATE AssemblerEngine.API)
find_package(OpenGL REQUIRED)
target_link_libraries(ae_opengl_backend PUBLIC opengl32)