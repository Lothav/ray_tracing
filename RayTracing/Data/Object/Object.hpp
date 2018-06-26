//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_OBJECT_HPP
#define RAY_TRACING_OBJECT_HPP

#include "../../Ray.hpp"

namespace RayTracing
{
    class Object
    {

        int pigment_index_;
        int finish_index_;

    protected:

        Object(int pigment_index, int finish_index) : pigment_index_(pigment_index), finish_index_(finish_index) {}

    public:

        virtual bool checkIntersection(Ray* ray)
        {
            return false;
        };

    };
}



#endif //RAY_TRACING_OBJECT_HPP
