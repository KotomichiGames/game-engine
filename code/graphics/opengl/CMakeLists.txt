#=======================================================================================================================
target_precompile_headers(${PROJECT_NAME} PRIVATE private.hpp)
target_link_libraries(${PROJECT_NAME}     PRIVATE engine::core glad)
target_sources(${PROJECT_NAME}            PRIVATE commands.cpp functions.cpp)
#=======================================================================================================================