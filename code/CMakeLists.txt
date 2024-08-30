#=======================================================================================================================
add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(platform)
#=======================================================================================================================
add_library(engine::core     ALIAS engine_core)
add_library(engine::platform ALIAS engine_platform)
add_library(engine::graphics ALIAS engine_graphics)
#=======================================================================================================================