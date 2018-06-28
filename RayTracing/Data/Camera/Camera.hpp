//
// Created by luiz0tavio on 6/23/18.
//

#ifndef RAY_TRACING_CAMERA_HPP
#define RAY_TRACING_CAMERA_HPP

#include <glm/vec3.hpp>

namespace RayTracing
{
    class Camera
    {

    private:

        glm::vec3   eye_;       // Camera position.
        glm::vec3   center_;    // Where camera is point to.
        glm::vec3   up_;        // Camera normal vector.

        float       fov_;       // Field of view.

    public:

        Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, float fov) : eye_(eye), center_(center), up_(up), fov_(fov) {}

        glm::vec3 getEye() const
        {
            return eye_;
        }

        glm::vec3 getCenter() const
        {
            return center_;
        }

        glm::vec3 getUp() const
        {
            return up_;
        }

        float getFov() const
        {
            return fov_;
        }

    };

}
#endif //RAY_TRACING_CAMERA_HPP
