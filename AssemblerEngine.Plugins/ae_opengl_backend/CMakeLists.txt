
if (WIN32)
	add_library(ae_opengl_backend SHARED 
	"win32_opengl_backend.c" 
	"glad.c"
	"opengl_shader.c"
	"opengl_renderer.c")
elseif(UNIX)
	add_library(ae_window SHARED
	"glad.c"
	"linux_opengl_backend.c" 
	"opengl_shader.c"
	"opengl_renderer.c")
endif (WIN32)


target_link_libraries(ae_opengl_backend PRIVATE AssemblerEngine.API)
find_package(OpenGL REQUIRED)
target_link_libraries(ae_opengl_backend PUBLIC opengl32)