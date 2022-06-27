cmake_minimum_required(VERSION "3.16.3")

project(model-load)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)

include_directories(includes)
include_directories(includes/external)

if(WIN32)
link_directories(lib)
endif()

add_executable(
    model-load

    src/Main.cpp
    src/external/glad.c
    src/external/stb_image.cpp
    includes/external/imgui/imgui.cpp
    includes/external/imgui/imgui_draw.cpp
    includes/external/imgui/imgui_demo.cpp
    includes/external/imgui/imgui_widgets.cpp
    includes/external/imgui/imgui_tables.cpp
    includes/external/imgui/imgui_impl_glfw.cpp
    includes/external/imgui/imgui_impl_opengl3.cpp
)

target_link_libraries(model-load ${CMAKE_DL_LIBS})
if(WIN32)
target_link_libraries(
        model-load
        ${glfw_LIBRARIES}
)
target_link_libraries(model-load glfw3)
else()
target_link_libraries(model-load glfw)
endif()
