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

        glm::vec3 getPos() const
        {
            return pos_;
        }

        glm::vec3 getPos(int index) const
        {
            float coefficient = 30.f;

            switch (index % 8) {
                case 0:

                    return glm::vec3(pos_.x - coefficient, pos_.y, pos_.z);
                case 1:
                    return glm::vec3(pos_.x - coefficient, pos_.y + coefficient, pos_.z);
                case 2:
                    return glm::vec3(pos_.x, pos_.y + coefficient, pos_.z);
                case 3:
                    return glm::vec3(pos_.x + coefficient, pos_.y + coefficient, pos_.z);
                case 4:
                    return glm::vec3(pos_.x + coefficient, pos_.y, pos_.z);
                case 5:
                    return glm::vec3(pos_.x + coefficient, pos_.y - coefficient, pos_.z);
                case 6:
                    return glm::vec3(pos_.x, pos_.y - coefficient, pos_.z);
                case 7:
                    return glm::vec3(pos_.x - coefficient, pos_.y - coefficient, pos_.z);
                default:
                    return pos_;
            }

        }

        glm::vec3 getColor() const
        {
            return color_;
        }

        glm::vec3 getMitigation() const
        {
            return mitigation_;
        }

    };

}



#endif //RAY_TRACING_LIGHT_HPP
