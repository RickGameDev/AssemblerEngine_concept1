add_library (${CMAKE_PROJECT_NAME}_DLL "src/main.c")
set_target_properties("${PROJECT_NAME}_DLL" PROPERTIES OUTPUT_NAME ${PROJECT_NAME})