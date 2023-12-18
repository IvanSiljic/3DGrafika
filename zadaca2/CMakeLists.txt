cmake_minimum_required(VERSION 3.26)
project(3DGrafika C)

set(CMAKE_C_STANDARD 11)

include_directories(..)
include_directories(.)

add_executable(3DGrafika
        geometry.h
        image.h
        ray.h
        objects.h)
