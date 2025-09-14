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

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

add_library(crumb_engine
    src/glad.c 
    src/Rendering/Renderer2D.cpp
    src/Rendering/Sprite.cpp
    src/Rendering/Shader.cpp
    src/Core/Application.cpp
    src/Core/AssetManager.cpp
    src/Core/InputManager.cpp
    src/Core/Engine.cpp
    src/Utilities/KeyUtils.cpp
    src/Scene/GameObject.cpp
    src/Scene/Scene.cpp
)

target_include_directories(crumb_engine 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PRIVATE 
        dependencies
        dependencies/stb
)

target_compile_definitions(crumb_engine PRIVATE GLFW_STATIC)
target_link_libraries(crumb_engine PUBLIC glfw OpenGL::GL glm::glm)

add_executable(test_game
    examples/TestGame/main.cpp
    examples/TestGame/TestApplication.cpp
    examples/TestGame/GameObjects/Player.cpp
)

target_link_libraries(test_game PRIVATE crumb_engine)

add_custom_command(TARGET test_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:test_game>/assets
)