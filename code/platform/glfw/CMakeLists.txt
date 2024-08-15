#=======================================================================================================================
target_precompile_headers(${PROJECT_NAME} PRIVATE private.hpp)
target_link_libraries(${PROJECT_NAME}     PRIVATE glfw)
target_sources(${PROJECT_NAME}            PRIVATE window.cpp factory.cpp)
#=======================================================================================================================