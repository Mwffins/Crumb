cmake_minimum_required(VERSION 3.14)
project(crumb VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG latest
)
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

add_executable(crumb 
    src/main.cpp 
    src/glad.c 
    src/Rendering/Shader.cpp
    src/Core/Application.cpp
    src/Core/Engine.cpp
)

target_include_directories(crumb PRIVATE dependencies)

target_compile_definitions(crumb PRIVATE GLFW_STATIC)

target_link_libraries(crumb PRIVATE glfw OpenGL::GL)

add_custom_command(TARGET crumb POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:crumb>/assets
)