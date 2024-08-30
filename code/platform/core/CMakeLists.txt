#=======================================================================================================================
target_link_libraries(${PROJECT_NAME} PRIVATE engine::core)
target_sources(${PROJECT_NAME}        PRIVATE window_factory.cpp window_manager.cpp input_manager.cpp)
#=======================================================================================================================