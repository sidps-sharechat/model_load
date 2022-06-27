cmake_minimum_required(VERSION "3.16.3")

project(model-load)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(ASSIMP REQUIRED)
if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
endif() 

include_directories(includes)
include_directories(includes/external)
include_directories(configuration)

if(WIN32)
link_directories(lib)
endif()

add_executable(
    model-load

    src/Main.cpp
    src/external/glad.c
    src/external/stb_image.cpp
    src/FileSystem.cpp
    src/Camera.cpp
    src/Transform.cpp
    src/Texture.cpp
    src/Shader.cpp
    src/Renderer.cpp
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
target_link_libraries(model-load assimp)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

if(WIN32)
add_custom_command(TARGET model-load POST_BUILD   
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/dlls/assimp-vc142-mtd.dll"
        $<TARGET_FILE_DIR:model-load>)    
endif()