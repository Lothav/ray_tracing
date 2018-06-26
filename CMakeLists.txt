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

        RayTracing/Data/Camera/Camera.hpp
        RayTracing/Data/Camera/Camera.cpp
        RayTracing/Data/Light/Light.hpp
        RayTracing/Data/Light/Light.cpp
        RayTracing/Data/Pigment/Pigment.hpp
        RayTracing/Data/Pigment/Pigment.cpp
        RayTracing/Data/Pigment/Solid.cpp
        RayTracing/Data/Pigment/Solid.hpp
        RayTracing/Data/Pigment/Checker.cpp
        RayTracing/Data/Pigment/Checker.hpp
        RayTracing/Data/Pigment/TextureMap.cpp
        RayTracing/Data/Pigment/TextureMap.hpp
        RayTracing/Data/Finishing/Finishing.cpp
        RayTracing/Data/Finishing/Finishing.hpp
        RayTracing/Data/Object/Object.cpp
        RayTracing/Data/Object/Object.hpp
        RayTracing/Data/Object/Sphere.cpp
        RayTracing/Data/Object/Sphere.hpp
        RayTracing/Data/Object/Polyhedron.cpp
        RayTracing/Data/Object/Polyhedron.hpp
        RayTracing/Data/Data.hpp
        RayTracing/RayTracing.hpp RayTracing/RayTracing.cpp RayTracing/RayTracing.hpp)