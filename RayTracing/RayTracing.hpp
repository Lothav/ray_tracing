//
// Created by luiz0tavio on 6/26/18.
//

#ifndef RAY_TRACING_RAYTRACING_HPP
#define RAY_TRACING_RAYTRACING_HPP


#include "Data/Data.hpp"

namespace RayTracing
{

    class RayTracing {

    private:

        Data* data_ = nullptr;

        std::vector<std::vector<glm::vec3>> color_map_;

    public:

        RayTracing(Data* data) : data_(data) {}

        std::vector<std::vector<glm::vec3>> getColorMap() const
        {
            return color_map_;
        }

        void fillColorMap()
        {
            auto* camera = data_->getCamera();

            auto camera_eye                  = camera->getEye();
            auto camera_center               = camera->getCenter();
            auto camera_up                   = camera->getUp();

            auto projection_plane_normal     = glm::normalize(camera_eye - camera_center);
            float projection_plane_d         = -(glm::dot(camera_center, projection_plane_normal));
            auto projection_plane_equation   = glm::vec4(projection_plane_normal, projection_plane_d);

            float projection_plane_len       = glm::length(camera_eye - camera_center) * glm::tan(glm::radians(camera->getFov()));

            auto x = camera_center.x - projection_plane_len;
            auto y = camera_center.y - projection_plane_len;
            auto z = -((projection_plane_equation.x * x) + (projection_plane_equation.y * y) + projection_plane_d) / (projection_plane_equation.z);

            auto lower_left_corner = glm::vec3(x, y, z);

            for (int i = 0; i < projection_plane_len * 2; i++) {
                this->color_map_.push_back({});
                for (int j = 0; j < projection_plane_len * 2; j++) {

                    auto u = static_cast<float>(i) / (projection_plane_len * 2);
                    auto v = static_cast<float>(j) / (projection_plane_len * 2);

                    auto direction = lower_left_corner + u*glm::vec3(projection_plane_len*2, 0, 0) + v*glm::vec3(0, projection_plane_len*2, 0);
                    direction.z = -((projection_plane_equation.x * direction.x) + (projection_plane_equation.y * direction.y) + projection_plane_d) / (projection_plane_equation.z);

                    auto* ray = new Ray(camera->getEye(), direction);

                    glm::vec3 color(.0f);
                    for (auto& object : data_->getObjects()) {
                        if (object->checkIntersection(ray)) {
                            color = data_->getPigment()[object->getPigmentIndex()]->getColor(glm::vec3(direction), camera_center);
                        }
                    }

                    this->color_map_[this->color_map_.size()-1].push_back(color);

                    delete ray;
                }
            }
        }

    };

}

#endif //RAY_TRACING_RAYTRACING_HPP
