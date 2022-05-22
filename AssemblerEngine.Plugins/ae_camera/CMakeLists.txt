add_library(ae_camera SHARED 
"camera.c"
)
target_link_libraries(ae_camera PRIVATE AssemblerEngine.API)