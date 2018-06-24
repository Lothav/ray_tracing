//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_FINISHING_HPP
#define RAY_TRACING_FINISHING_HPP

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace RayTracing
{
    class Finishing
    {

    private:

        glm::vec4 light_coefficients_;
        glm::vec3 model_coefficients_;

    public:

        Finishing(glm::vec4 light_coefficients_, glm::vec3 model_coefficients_) : light_coefficients_(), model_coefficients_() {}

    };
}


#endif //RAY_TRACING_FINISHING_HPP
