cmake_minimum_required(VERSION 3.10)
project(ray_tracing)
set(CMAKE_CXX_STANDARD 17)
add_executable(
        ray_tracing
        main.cpp
        Camera/Camera.hpp
        Camera/Camera.cpp
        Light/Light.hpp
        Light/Light.cpp
        Pigment/Pigment.hpp
        Pigment/Pigment.cpp
        Pigment/Solid.cpp
        Pigment/Solid.hpp
        Pigment/Checker.cpp
        Pigment/Checker.hpp
        Pigment/TextureMap.cpp
        Pigment/TextureMap.hpp
        Finishing/Finishing.cpp
        Finishing/Finishing.hpp
        Util/Util.cpp
        Util/Util.hpp
        Util/File.cpp
        Util/File.hpp
        Object/Object.cpp Object/Object.hpp Object/Sphere.cpp Object/Sphere.hpp Object/Polyhedron.cpp Object/Polyhedron.hpp)