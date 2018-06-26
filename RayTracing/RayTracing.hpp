//
// Created by luiz0tavio on 6/26/18.
//

#ifndef RAY_TRACING_RAYTRACING_HPP
#define RAY_TRACING_RAYTRACING_HPP


#include "Data/Data.hpp"

namespace RayTracing
{

    class RayTracing {

    private:

        Data * data_ = nullptr;

    public:

        RayTracing(Data* data) : data_(data) {}

        void dispatchRay()
        {
            auto ray = new Ray({.0f, .0f, .0f}, {.0f, .0f, 1.f});
            data_->checkIntersection(ray);
        }

    };

}

#endif //RAY_TRACING_RAYTRACING_HPP
