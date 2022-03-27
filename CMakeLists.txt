cmake_minimum_required(VERSION 3.13)
project(model_viewer)

set(CMAKE_CXX_STANDARD 20)

add_executable(model_viewer
        src/engine/gl/Cubemap.cpp
        src/engine/gl/Cubemap.h
        src/engine/gl/glad.c
        src/engine/gl/glad.h
        src/engine/gl/Program.cpp
        src/engine/gl/Program.h
        src/engine/gl/Texture.cpp
        src/engine/gl/Texture.h
        src/engine/gl/Texture2D.cpp
        src/engine/gl/Texture2D.h
        src/engine/Camera.cpp
        src/engine/Camera.h
        src/engine/Material.h
        src/engine/Mesh.cpp
        src/engine/Mesh.h
        src/engine/Model.cpp
        src/engine/Model.h
        src/engine/stb_image.c
        src/engine/stb_image.h
        src/math/math.h
        src/Game.cpp
        src/Game.h
        src/main.cpp src/engine/gl/buffers.cpp src/engine/gl/buffers.h src/engine/gl/VAO.cpp src/engine/gl/VAO.h src/engine/gl/FrameBuffer.cpp src/engine/gl/FrameBuffer.h)

target_compile_options(model_viewer PUBLIC -Werror -Wall -Wextra -Wno-unused-parameter -Wno-error=unused-function)
target_link_libraries(model_viewer glfw dl assimp)