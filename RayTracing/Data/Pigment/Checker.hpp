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

        Checker(glm::vec3 color_a, glm::vec3 color_b, float size) : color_a_(color_a), color_b_(color_b), size_(size/10) {}

        glm::vec3 getColor(glm::vec3 pos, glm::vec3 plane_point) override
        {
            auto z_factor = size_/ abs(1/pos.z - 1/plane_point.z );

            auto color = pos.x < 0.f ? color_a_ : color_b_;

            if (static_cast<int>(pos.x / z_factor) % 2 == 0) {
                color = pos.x < 0.f ? color_b_ : color_a_;
            }

            if (static_cast<int>(pos.y / z_factor) % 2 == 0) {
                color = color == color_a_ ? color_b_ : color_a_;
            }

            return color;
        }

    };
}

#endif //RAY_TRACING_CHECKER_HPP
