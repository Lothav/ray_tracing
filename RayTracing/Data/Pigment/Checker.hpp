//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_CHECKER_HPP
#define RAY_TRACING_CHECKER_HPP

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include "Pigment.hpp"

namespace RayTracing
{
    class Checker : public Pigment
    {

    private:

        glm::vec3 color_a_;
        glm::vec3 color_b_;

        float size_;

    public:

        Checker(glm::vec3 color_a, glm::vec3 color_b, float size) : color_a_(color_a), color_b_(color_b), size_(size) {}

        glm::vec3 getColor(glm::vec3 pos, glm::vec3 plane_point) override
        {
            auto distance = glm::length(plane_point - pos);

            if (static_cast<int>(distance / size_) % 2 == 0) {
                return color_a_;
            }

            return color_b_;
        }

    };
}

#endif //RAY_TRACING_CHECKER_HPP
