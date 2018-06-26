//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_SPHERE_HPP
#define RAY_TRACING_SPHERE_HPP

#include <glm/vec3.hpp>
#include "Object.hpp"

namespace RayTracing
{
    class Sphere : public Object
    {

    private:

        glm::vec3   pos_;
        float       radius_;

    public:

        Sphere(int pigment_index, int finish_index, glm::vec3 pos, float radius)
                : Object(pigment_index, finish_index), pos_(pos), radius_(radius) {}

        bool checkIntersection(Ray* ray) override
        {
            return false;
        };
    };
}


#endif //RAY_TRACING_SPHERE_HPP
