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
