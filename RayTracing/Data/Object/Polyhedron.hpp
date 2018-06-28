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

        Polyhedron(int pigment_index, int finish_index) : Object(pigment_index, finish_index), planes_({}) {}

        void addPlane(glm::vec4 plane)
        {
            this->planes_.push_back(plane);
        }

        bool checkIntersection(Ray* ray) override
        {
            auto ray_origin     = ray->getOrigin();
            auto ray_direction  = ray->getDirection();

            for (auto& plane : planes_) {

                float dot_plane_vec = glm::dot(ray_direction - ray_origin, glm::vec3(plane));

                // check parallel
                if (dot_plane_vec == 0.f) {
                    return false;
                }

                auto s1 = -(plane.x * ray_origin.x
                          + plane.y * ray_origin.y
                          + plane.z * ray_origin.z
                          + plane.w) / dot_plane_vec;

                return s1 <= 0.f;
            }
            return true;
        }

    };
}

#endif //RAY_TRACING_POLYHEDRON_HPP
