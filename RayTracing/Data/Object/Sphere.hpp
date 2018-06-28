//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_SPHERE_HPP
#define RAY_TRACING_SPHERE_HPP

#include <glm/glm.hpp>

#include "Object.hpp"

namespace RayTracing
{
    class Sphere : public Object
    {

    private:

        glm::vec3   center_;
        float       radius_;

    public:

        Sphere(int pigment_index, int finish_index, glm::vec3 center, float radius)
                : Object(pigment_index, finish_index), center_(center), radius_(radius) {}

        bool checkIntersection(Ray* ray) override
        {
            glm::vec3 oc = ray->getOrigin() - center_;

            auto a = glm::dot(ray->getDirection(), ray->getDirection());
            auto b = 2.0f * glm::dot(oc, ray->getDirection());
            auto c = glm::dot(oc, oc) - radius_*radius_;

            return (b*b - 4*a*c) >= 0;
        };
    };
}


#endif //RAY_TRACING_SPHERE_HPP
