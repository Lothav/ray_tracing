//
// Created by luiz0tavio on 6/23/18.
//

#ifndef RAY_TRACING_LIGHT_HPP
#define RAY_TRACING_LIGHT_HPP


#include <glm/vec3.hpp>

namespace RayTracing
{
    class Light
    {

    private:

        glm::vec3 pos_;
        glm::vec3 color_;
        glm::vec3 mitigation_;

    public:

        Light(glm::vec3 pos, glm::vec3 color, glm::vec3 mitigation) : pos_(pos), color_(color), mitigation_(mitigation) {}

        glm::vec3 getPos()
        {
            return pos_;
        }


    };

}



#endif //RAY_TRACING_LIGHT_HPP
