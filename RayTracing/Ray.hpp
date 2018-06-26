//
// Created by luiz0tavio on 6/26/18.
//

#ifndef RAY_TRACING_RAY_HPP
#define RAY_TRACING_RAY_HPP

#include <glm/vec3.hpp>

namespace RayTracing
{
    class Ray
    {

    private:

        glm::vec3 origin_;
        glm::vec3 direction_;

    public:

        Ray (glm::vec3 origin, glm::vec3 direction) : origin_(origin), direction_(direction) {}

    };
}

#endif //RAY_TRACING_RAY_HPP
