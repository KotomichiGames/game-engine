#=======================================================================================================================
add_library(${PROJECT_NAME})
#=======================================================================================================================
target_include_directories(${PROJECT_NAME} PUBLIC ..)
target_precompile_headers(${PROJECT_NAME}  PUBLIC public.hpp)
#=======================================================================================================================
target_link_libraries(${PROJECT_NAME}     PRIVATE engine_core)
target_sources(${PROJECT_NAME}            PRIVATE window_factory.cpp window_manager.cpp input_manager.cpp)
#=======================================================================================================================