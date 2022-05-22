add_library(ae_logging SHARED 
"logging.c"
)
target_link_libraries(ae_logging PRIVATE AssemblerEngine.API)