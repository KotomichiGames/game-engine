#=======================================================================================================================
project(engine_platform)
#=======================================================================================================================
add_library(${PROJECT_NAME})
#=======================================================================================================================
target_compile_features(${PROJECT_NAME}    PUBLIC cxx_std_23)
target_precompile_headers(${PROJECT_NAME}  PUBLIC public.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#=======================================================================================================================
target_link_libraries(${PROJECT_NAME} PRIVATE engine::core)
target_sources(${PROJECT_NAME}        PRIVATE window_factory.cpp window_manager.cpp)
#=======================================================================================================================
add_subdirectory(windows)
add_subdirectory(glfw)
#=======================================================================================================================