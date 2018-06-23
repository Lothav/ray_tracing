cmake_minimum_required(VERSION 3.10)
project(ray_tracing)
set(CMAKE_CXX_STANDARD 11)
add_executable(ray_tracing main.cpp Camera.hpp Camera.cpp)