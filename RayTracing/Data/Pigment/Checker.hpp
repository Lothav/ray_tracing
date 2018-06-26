//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_CHECKER_HPP
#define RAY_TRACING_CHECKER_HPP

#include <glm/vec3.hpp>
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

    };
}

#endif //RAY_TRACING_CHECKER_HPP
