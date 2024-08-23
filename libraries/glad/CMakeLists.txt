project(glad)

add_library(${PROJECT_NAME} glad.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)