//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_OBJECT_HPP
#define RAY_TRACING_OBJECT_HPP

#include "../../Ray.hpp"
#include <vector>

namespace RayTracing
{
    class Object
    {

        int pigment_index_;
        int finish_index_;

    protected:

        Object(int pigment_index, int finish_index) : pigment_index_(pigment_index), finish_index_(finish_index) {}

    public:

        virtual std::vector<glm::vec3> getIntersections(Ray* ray)
        {
            return {};
        };

        int getPigmentIndex() const
        {
            return pigment_index_;
        }

    };
}



#endif //RAY_TRACING_OBJECT_HPP
