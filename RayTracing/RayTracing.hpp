//
// Created by luiz0tavio on 6/26/18.
//

#ifndef RAY_TRACING_RAYTRACING_HPP
#define RAY_TRACING_RAYTRACING_HPP

#include <algorithm>    // std::max
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

                    auto* d_ray = new Ray(camera->getEye(), direction);
                    auto final_color = getFinalColor(d_ray);

                    this->color_map_[this->color_map_.size()-1].push_back(final_color);
                }
            }
        }

    private:

        glm::vec3 getFinalColor(Ray* d_ray)
        {
            auto* camera  = data_->getCamera();
            auto lights   = data_->getLights();
            auto pigments = data_->getPigment();
            auto finishes = data_->getFinishes();

            glm::vec3 min_intersection = {};
            Object*   near_object = nullptr;

            glm::vec3 final_color(.0f);
            if (getIntersection(d_ray, near_object, min_intersection, nullptr)) {

                auto ambient_light = lights[0];

                auto finish  = finishes[near_object->getFinishIndex()];
                auto light_c = finish->getLightCoefficients();
                auto model_c = finish->getModelCoefficients();
                auto N = near_object->getNormal(min_intersection);
                auto V = glm::normalize(camera->getEye() - min_intersection);

                auto pigment = pigments[near_object->getPigmentIndex()]->getColor(min_intersection) ;

                glm::vec3 ambient = ambient_light->getColor() * light_c.x;
                glm::vec3 diffuse(0.f);
                float specular = 0.f;

                for (int k = 1; k < lights.size(); ++k) {

                    auto l_pos   = lights[k]->getPos();
                    auto l_color = lights[k]->getColor();
                    auto* l_ray  = new Ray(min_intersection, l_pos - min_intersection);

                    glm::vec3 l_min_intersection = {};
                    Object*   l_near_object = nullptr;

                    auto found_i = getIntersection(l_ray, l_near_object, l_min_intersection, near_object);

                    auto dist_l  = glm::length(l_pos - min_intersection);
                    auto dist_i  = glm::length(l_min_intersection - min_intersection);

                    if (!found_i || dist_l < dist_i) {

                        auto L = glm::normalize(l_pos - min_intersection);
                        auto R = glm::reflect(-L, N);

                        diffuse  += light_c.y * l_color * std::max(glm::dot(N, L), 0.0f) * glm::vec3(1.0f);
                        specular += light_c.z * pow(std::max(glm::dot(R, V), 0.0f), light_c.w) * 1.0f; // 1.0f = alpha
                    }

                    delete l_ray;
                }

                final_color = pigment*(ambient + diffuse) + specular;

                if (model_c.x > 0.f) {
                    auto R = glm::reflect(-V, N);
                    final_color += model_c.x * getFinalColor(new Ray(min_intersection, min_intersection+R));
                }
            }
            delete d_ray;

            return final_color;
        }

        bool getIntersection(Ray* ray, Object*& near_object, glm::vec3& min_intersection, Object* from_object)
        {
            auto* camera        = data_->getCamera();
            float min_distance  = MAXFLOAT;
            bool  found         = false;

            for (auto& object : data_->getObjects()) {
                if(from_object == object) {
                    continue;
                }

                auto intersections = object->getIntersections(ray);
                if (intersections.empty()) continue;

                for (auto &intersection : intersections) {
                    auto distance = static_cast<float>(glm::length(camera->getEye() - intersection));
                    if (distance < min_distance) {
                        if (ray->getOrigin() == intersection) continue;

                        near_object      = object;
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
