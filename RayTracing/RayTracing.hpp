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

        std::vector<std::vector<uint>> color_map;

    public:

        RayTracing(Data* data) : data_(data) {}

        void fillColorMap()
        {
            auto* camera = data_->getCamera();

            auto camera_eye                  = camera->getEye();
            auto camera_center               = camera->getCenter();

            auto projection_plane_normal     = glm::normalize(camera_eye - camera_center);
            float projection_plane_d         = -(glm::dot(camera_center, projection_plane_normal));
            auto projection_plane_equation   = glm::vec4(projection_plane_normal, projection_plane_d);

            int projection_plane_len         = glm::length(camera_eye - camera_center) * glm::tan(glm::radians(camera->getFov())) * 2;

            for (int i = 0; i < projection_plane_len; i++) {
                for (int j = 0; j < projection_plane_len; j--) {

                    auto u = static_cast<float>(i) / static_cast<float>(projection_plane_len);
                    auto v = static_cast<float>(j) / static_cast<float>(projection_plane_len);

                    auto* ray = new Ray(camera->getEye(), lower_left_corner + u*horizontal + v*vertical);

                    uint color = 0;
                    for (auto& object : data_->getObjects()) {
                        if (object->checkIntersection(ray)) {
                            color = 1;
                            break;
                        }
                    }

                    this->color_map[this->color_map.size()-1].push_back(color);

                    delete ray;
                }
            }
        }

    };

}

#endif //RAY_TRACING_RAYTRACING_HPP
