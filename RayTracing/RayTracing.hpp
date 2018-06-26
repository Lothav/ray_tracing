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

        void dispatchRay(Ray* ray)
        {
            data_->checkIntersection(ray);
        }

        void fillColorMap(uint nx, uint ny)
        {
            auto* camera = data_->getCamera();

            glm::vec3 lower_left_corner = {-2.0, -1.0, -1.0};
            glm::vec3 horizontal = {4.0, .0, .0};
            glm::vec3 vertical = {.0, 2.0, .0};

            for (int j = ny-1; j >= 0; j--) {
                for (int i = 0; i < nx; i++) {

                    auto u = static_cast<float>(i) / static_cast<float>(nx);
                    auto v = static_cast<float>(j) / static_cast<float>(ny);

                    auto* ray = new Ray(camera->getCenter(), lower_left_corner + u*horizontal + v*vertical);

                    for (auto& object : data_->getObjects()) {
                        this->color_map.push_back(object->checkIntersection(ray) ? : )
                    }

                    delete ray;
                }
            }
        }

    };

}

#endif //RAY_TRACING_RAYTRACING_HPP
