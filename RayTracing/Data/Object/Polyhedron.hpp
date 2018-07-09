//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_POLYHEDRON_HPP
#define RAY_TRACING_POLYHEDRON_HPP

#include <glm/vec4.hpp>
#include <vector>
#include <glm/geometric.hpp>
#include <array>
#include <iostream>
#include "Object.hpp"

#define EPSILON 0.001

namespace RayTracing
{
    class Polyhedron : public Object
    {

    private:

        std::vector<glm::vec4> planes_;

    public:

        Polyhedron(uint pigment_index, uint finish_index) : Object(pigment_index, finish_index), planes_({}) {}

        void addPlane(glm::vec4 plane)
        {
            this->planes_.push_back(plane);
        }

        glm::vec3 getNormal(glm::vec3 point) override
        {
            for (auto plane : planes_) {
                float d = plane.x * point.x + plane.y * point.y + plane.z * point.z;
                if (std::fabs(plane.w + d) < EPSILON) {
                    return glm::normalize(glm::vec3(plane));
                }
            }
            std::cerr << "Cant find Polyhedron normal!" << std::endl;
            return {};
        }

        /**
         * Polyhedron intersection method described in
         * Book:    Graphic Gems II
         * Section: FAST RAY-CONVEX POLYHEDRON INTERSECTION
         * Page:    247
         * */
        std::vector<glm::vec3> getIntersections(const std::shared_ptr<Ray>& ray) override
        {
            std::vector<glm::vec3> intersections = {};

            auto ray_origin     = ray->getOrigin();
            auto ray_direction  = ray->getDirection();

            float t_near = -MAXFLOAT;
            float t_far  = MAXFLOAT;

            std::array<int, 2> indexes = {-1, -1};

            for (int j = 0; j < planes_.size(); ++j) {
                auto plane = planes_[j];

                auto U_n = glm::dot(ray_origin, glm::vec3(plane)) + plane.w;
                auto U_d = glm::dot(ray_direction, glm::vec3(plane));

                // check parallel
                if (U_d == 0.f && U_n > 0.f) {
                    continue;
                }

                auto t = -U_n/U_d;
                if (t < 0.f) {
                    continue;
                }

                if(U_d > 0.f){
                    // Back-face plane
                    if (t < t_far) {
                        t_far = t;
                        indexes[0] = j;
                    }
                } else {
                    // Front-face plane
                    if (t > t_near) {
                        t_near = t;
                        indexes[1] = j;
                    }
                }

                if (t_near > t_far) {
                    return {};
                }

            }

            if (indexes[0] != -1 && indexes[1] != -1) {
                for (int index : indexes) {
                    auto plane = planes_[index];

                    auto U_d = static_cast<float>(glm::dot(ray_direction, glm::vec3(plane)));
                    auto s1 = -(plane.x * ray_origin.x + plane.y * ray_origin.y + plane.z * ray_origin.z + plane.w) / U_d;

                    intersections.push_back(ray_origin + (ray_direction * s1));
                }
            }

            return intersections;
        }

    };
}

#endif //RAY_TRACING_POLYHEDRON_HPP
