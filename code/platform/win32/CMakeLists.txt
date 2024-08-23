#=======================================================================================================================
target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN)
target_precompile_headers(${PROJECT_NAME}  PRIVATE private.hpp)
target_link_libraries(${PROJECT_NAME}      PRIVATE user32 opengl32)
target_sources(${PROJECT_NAME}             PRIVATE context.cpp window.cpp window_events.cpp factory.cpp)
#=======================================================================================================================