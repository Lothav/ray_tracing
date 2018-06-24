cmake_minimum_required(VERSION 3.10)
project(ray_tracing)
set(CMAKE_CXX_STANDARD 17)
add_executable(
        ray_tracing
        main.cpp

        Util/Util.cpp
        Util/Util.hpp
        Util/File.cpp
        Util/File.hpp

        RayTracing/Camera/Camera.hpp
        RayTracing/Camera/Camera.cpp
        RayTracing/Light/Light.hpp
        RayTracing/Light/Light.cpp
        RayTracing/Pigment/Pigment.hpp
        RayTracing/Pigment/Pigment.cpp
        RayTracing/Pigment/Solid.cpp
        RayTracing/Pigment/Solid.hpp
        RayTracing/Pigment/Checker.cpp
        RayTracing/Pigment/Checker.hpp
        RayTracing/Pigment/TextureMap.cpp
        RayTracing/Pigment/TextureMap.hpp
        RayTracing/Finishing/Finishing.cpp
        RayTracing/Finishing/Finishing.hpp
        RayTracing/Object/Object.cpp
        RayTracing/Object/Object.hpp
        RayTracing/Object/Sphere.cpp
        RayTracing/Object/Sphere.hpp
        RayTracing/Object/Polyhedron.cpp
        RayTracing/Object/Polyhedron.hpp
        RayTracing/Data.hpp
)