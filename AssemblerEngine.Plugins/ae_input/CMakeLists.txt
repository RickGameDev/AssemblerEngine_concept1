add_library(ae_input SHARED 
"input.c"
)
target_link_libraries(ae_input PRIVATE AssemblerEngine.API)