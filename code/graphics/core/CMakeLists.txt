#=======================================================================================================================
target_precompile_headers(${PROJECT_NAME} PRIVATE private.hpp)
target_compile_features(${PROJECT_NAME}   PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME}     PRIVATE engine::core)
target_sources(${PROJECT_NAME}            PRIVATE buffer_data.cpp)
#=======================================================================================================================