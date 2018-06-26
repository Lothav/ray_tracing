//
// Created by luiz0tavio on 6/26/18.
//

#ifndef RAY_TRACING_RAYTRACING_HPP
#define RAY_TRACING_RAYTRACING_HPP


#include "Data/Data.hpp"

class RayTracing {

private:

    Data * data_ = nullptr;

public:

    RayTracing(Data* data) : data_(data) {}

};


#endif //RAY_TRACING_RAYTRACING_HPP
