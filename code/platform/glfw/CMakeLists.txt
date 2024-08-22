#=======================================================================================================================
target_precompile_headers(${PROJECT_NAME} PRIVATE private.hpp)
target_link_libraries(${PROJECT_NAME}     PRIVATE user32 gdi32 shell32 glfw)
target_sources(${PROJECT_NAME}            PRIVATE window.cpp platform.cpp context.cpp factory.cpp)
#=======================================================================================================================