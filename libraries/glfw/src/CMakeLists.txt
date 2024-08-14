add_library(${PROJECT_NAME} ${GLFW_LIBRARY_TYPE}
                            "${GLFW_SOURCE_DIR}/include/GLFW/glfw3.h"
                            "${GLFW_SOURCE_DIR}/include/GLFW/glfw3native.h"
                            internal.h platform.h context.c init.c input.c monitor.c platform.c window.c)

target_compile_definitions(${PROJECT_NAME} PRIVATE _GLFW_WIN32)

target_sources(${PROJECT_NAME} PRIVATE win32_module.c win32_time.c win32_thread.c)
target_sources(${PROJECT_NAME} PRIVATE win32_init.c win32_monitor.c win32_window.c wgl_context.c)

target_include_directories(${PROJECT_NAME} PUBLIC
                           "$<BUILD_INTERFACE:${GLFW_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_include_directories(${PROJECT_NAME} PRIVATE
                           "${GLFW_SOURCE_DIR}/src"
                           "${GLFW_BINARY_DIR}/src")
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

if (GLFW_BUILD_WIN32)
    list(APPEND glfw_PKG_LIBS "-lgdi32")
endif()

if (GLFW_BUILD_WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE _UNICODE)
endif()