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

        std::vector<glm::vec3> getIntersections(Ray* ray) override
        {
            std::vector<glm::vec3> intersections = {};

            auto ray_origin     = ray->getOrigin();
            auto ray_direction  = glm::normalize(ray->getDirection() - ray->getOrigin());

            for (auto& plane : planes_) {

                float dot_plane_vec = glm::dot(ray_direction, glm::vec3(plane));

                // check parallel
                if (dot_plane_vec == 0.f) {
                    continue;
                }

                auto s1 = -(plane.x * ray_origin.x
                          + plane.y * ray_origin.y
                          + plane.z * ray_origin.z
                          + plane.w) / dot_plane_vec;

                if (s1 <= 0.f) {
                    auto intersection_point = ray->getOrigin() + (ray_direction*s1);

                    intersections.push_back(intersection_point);
                }
            }

            return intersections;
        }

    };
}

#endif //RAY_TRACING_POLYHEDRON_HPP
