//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_SPHERE_HPP
#define RAY_TRACING_SPHERE_HPP

#include <glm/glm.hpp>

#include "Object.hpp"
#include <vector>

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

        std::vector<glm::vec3> getIntersections(Ray* ray) override
        {
            std::vector<glm::vec3> intersections = {};

            glm::vec3 oc = ray->getOrigin() - center_;
            auto ray_direction = ray->getDirection();

            auto a = glm::dot(ray_direction, ray_direction);
            auto b = 2.0f * glm::dot(oc, ray_direction);
            auto c = glm::dot(oc, oc) - radius_*radius_;

            auto d = b*b - 4*a*c;

            if (d >= 0) {
                auto x1 = (-b + glm::sqrt(d)) / (2*a);
                auto intersection = ray->getOrigin() + (ray_direction * x1);
                if (checkValidIntersection(ray, intersection)) {
                    intersections.push_back(intersection);
                }
            }

            if (d > 0) {
                auto x1 = (-b - glm::sqrt(d)) / (2*a);
                auto intersection = ray->getOrigin() + (ray_direction*x1);
                if (checkValidIntersection(ray, intersection)) {
                    intersections.push_back(intersection);
                }
            }

            return intersections;
        };

    private:

        bool checkValidIntersection(Ray* ray, glm::vec3 intersection)
        {
            auto origin_dist = glm::length(ray->getOrigin() - intersection);
            auto inters_dist = glm::length((ray->getOrigin()+ray->getDirection()) - intersection);

            return origin_dist > inters_dist;
        }

    };
}


#endif //RAY_TRACING_SPHERE_HPP
