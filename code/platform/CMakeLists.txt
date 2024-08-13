project(platform)

add_library(${PROJECT_NAME})

target_precompile_headers(${PROJECT_NAME}  PUBLIC public.hpp)
target_link_libraries(${PROJECT_NAME}      PUBLIC glfw)
target_include_directories(${PROJECT_NAME} PUBLIC .)

target_sources(${PROJECT_NAME} PRIVATE window.cpp)