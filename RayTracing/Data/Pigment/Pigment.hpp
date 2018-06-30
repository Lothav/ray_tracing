//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_PIGMENT_HPP
#define RAY_TRACING_PIGMENT_HPP
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace RayTracing
{
    class Pigment
    {

    protected:

        Pigment() {}

    public:

        virtual glm::vec3 getColor()
        {
            return glm::vec3(0.f, 0.f, 0.f);
        }

        virtual glm::vec3 getColor(glm::vec3 intersection)
        {
            return getColor();
        }

    };

}
#endif //RAY_TRACING_PIGMENT_HPP
