//
// Created by luiz0tavio on 6/23/18.
//

#ifndef RAY_TRACING_CAMERA_HPP
#define RAY_TRACING_CAMERA_HPP

#include <glm/vec3.hpp>

class Camera {

private:

    glm::vec3 eye_;
    glm::vec3 center_;
    glm::vec3 up_;

public:

    Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up) : eye_(eye), center_(center), up_(up) {}

};


#endif //RAY_TRACING_CAMERA_HPP
