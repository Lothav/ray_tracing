cmake_minimum_required(VERSION 3.10)
project(ray_tracing)
set(CMAKE_CXX_STANDARD 11)
add_executable(
        ray_tracing
        main.cpp
        RayTracing/Camera.hpp
        RayTracing/Camera.cpp
        RayTracing/Light.hpp
        RayTracing/Light.cpp
        RayTracing/Pigments.hpp
        RayTracing/Pigments.cpp
        RayTracing/Solid.cpp
        RayTracing/Solid.hpp RayTracing/Checker.cpp RayTracing/Checker.hpp RayTracing/TextureMap.cpp RayTracing/TextureMap.hpp)