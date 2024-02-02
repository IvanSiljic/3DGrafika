cmake_minimum_required(VERSION 3.26)
project(3D)

set(CMAKE_CXX_STANDARD 17)

set(OpenGlLinkers -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl)

add_executable(3D main.cpp glad.c
        shader.h
        stb_image.cpp
        camera.h)
target_link_libraries(3D ${OpenGlLinkers})
