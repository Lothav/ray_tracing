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
            auto* camera  = data_->getCamera();
            auto lights   = data_->getLights();
            auto pigments = data_->getPigment();

            auto camera_eye              = camera->getEye();
            auto camera_center           = camera->getCenter();
            auto camera_up               = camera->getUp();

            auto projection_plane_normal = glm::normalize(camera_eye - camera_center);
            auto projection_plane_d      = -static_cast<float>(glm::dot(camera_center, projection_plane_normal));
            auto projection_plane_len    = static_cast<float>(glm::length(camera_eye - camera_center) * glm::tan(glm::radians(90 - camera->getFov())));

            auto lower_left_corner = glm::vec3(
                camera_center.x - projection_plane_len,
                camera_center.y - projection_plane_len,
                camera_center.z - projection_plane_len
            );

            auto size = projection_plane_len * 2.f;

            for (int i = 0; i < size; i++) {
                this->color_map_.push_back({});
                for (int j = 0; j < size; j++) {

                    auto u = static_cast<float>(i) / size;
                    auto v = static_cast<float>(j) / size;

                    auto direction = lower_left_corner + u*glm::vec3(size, 0, 0) + v*glm::vec3(0, size, 0);
                    direction.z = -((camera_center.x * direction.x) + (camera_center.y * direction.y) + projection_plane_d) / (camera_center.z);

                    auto* ray = new Ray(camera->getEye(), direction);

                    glm::vec3 min_intersection = {};
                    Object*   near_object = nullptr;

                    glm::vec3 pigment(.0f);
                    if (getIntersection(ray, &near_object, min_intersection, {})) {
                        if (near_object != nullptr) {
                            pigment = pigments[near_object->getPigmentIndex()]->getColor(min_intersection);
                        }
                        for (auto light: lights) {
                            auto* ray_l = new Ray(min_intersection, light->getPos() - direction);
                            glm::vec3 l_min_intersection = {};
                            if (getIntersection(ray, &near_object, l_min_intersection, {min_intersection})) {
                                if (glm::length(light->getPos() - min_intersection) < glm::length(l_min_intersection - min_intersection)) {
                                    std::cout << "found" << std::endl;
                                }
                            }
                            delete ray_l;
                        }
                    }
                    delete ray;

                    this->color_map_[this->color_map_.size()-1].push_back(pigment);
                }
            }
        }

    private:

        bool getIntersection(Ray* ray, Object** near_object, glm::vec3& min_intersection, const std::vector<glm::vec3>& ignore_points)
        {
            auto* camera        = data_->getCamera();
            float min_distance  = MAXFLOAT;
            bool  found         = false;

            for (auto& object : data_->getObjects()) {

                auto intersections = object->getIntersections(ray);
                if (intersections.empty()) continue;

                for (auto &intersection : intersections) {
                    auto distance = static_cast<float>(glm::length(camera->getEye() - intersection));
                    if (distance < min_distance) {

                        bool ignore = false;
                        for (auto ignore_point : ignore_points){
                            if (ignore_point == intersection) {
                                ignore = true;
                                break;
                            }
                        }
                        if (ignore) continue;

                        *near_object     = object;
                        min_distance     = distance;
                        min_intersection = intersection;

                        found = true;
                    }
                }
            }

            return found;
        }

    };

}

#endif //RAY_TRACING_RAYTRACING_HPP
