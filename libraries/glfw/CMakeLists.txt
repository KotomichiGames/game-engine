project(glfw)

find_package(Threads REQUIRED)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include
                                           PRIVATE .)

target_compile_definitions(${PROJECT_NAME} PRIVATE _GLFW_WIN32)

target_sources(${PROJECT_NAME} PRIVATE win32_init.c win32_monitor.c win32_window.c wgl_context.c win32_module.c
                                       win32_time.c win32_thread.c context.c init.c input.c monitor.c platform.c window.c)

target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE _UNICODE)
target_link_libraries(${PROJECT_NAME}      PRIVATE Threads::Threads)