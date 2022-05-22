add_library(ae_imgui SHARED 
"imgui.c"
 "shaders.h" "imgui.h")
target_link_libraries(ae_imgui PRIVATE AssemblerEngine.API)