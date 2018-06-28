//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_POLYHEDRON_HPP
#define RAY_TRACING_POLYHEDRON_HPP

#include <glm/vec4.hpp>
#include <vector>
#include <glm/geometric.hpp>
#include "Object.hpp"

namespace RayTracing
{
    class Polyhedron : public Object
    {

    private:

        std::vector<glm::vec4> planes_;

    public:

        Polyhedron(int pigment_index, int finish_index)
                : Object(pigment_index, finish_index), planes_({}) {}

        void addPlane(glm::vec4 plane)
        {
            this->planes_.push_back(plane);
        }

        bool checkIntersection(Ray* ray) override
        {
            for (auto& plane : planes_) {
                // check parallel
                if (glm::dot(ray->getDirection() - ray->getOrigin(), glm::vec3(plane)) == 0.f) {
                    return false;
                }

                auto s1 = -(plane.x * ray->getOrigin().x + plane.y * ray->getOrigin().y + plane.z * ray->getOrigin().z + plane.w)
                          / (glm::dot(glm::vec3(plane), ray->getDirection() - ray->getOrigin()));

                return s1 <= 0.f;
            }
            return true;
        }

    };
}

#endif //RAY_TRACING_POLYHEDRON_HPP
