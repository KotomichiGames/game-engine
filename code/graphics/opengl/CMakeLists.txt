#=======================================================================================================================
target_precompile_headers(${PROJECT_NAME} PRIVATE private.hpp)
target_link_libraries(${PROJECT_NAME}     PRIVATE engine::core opengl32)
target_sources(${PROJECT_NAME}            PRIVATE commands.cpp buffer.cpp vertex_array.cpp functions.cpp shader_stage.cpp)
#=======================================================================================================================