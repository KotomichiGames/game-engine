#=======================================================================================================================
project(engine_core)
#=======================================================================================================================
add_library(${PROJECT_NAME})
#=======================================================================================================================
add_subdirectory(core)
#=======================================================================================================================
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_precompile_headers(${PROJECT_NAME}  PUBLIC public.hpp)
target_compile_features(${PROJECT_NAME}    PUBLIC cxx_std_23)
#=======================================================================================================================