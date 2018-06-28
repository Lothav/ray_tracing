//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_SOLID_HPP
#define RAY_TRACING_SOLID_HPP

#include "Pigment.hpp"

#include <glm/vec3.hpp>

namespace RayTracing
{
    class Solid : public Pigment
    {

    private:

        glm::vec3 color_;

    public:

        Solid(glm::vec3 color) : color_(color) {}

        glm::vec3 getColor() override
        {
            return color_;
        }

    };
}

#endif //RAY_TRACING_SOLID_HPP
