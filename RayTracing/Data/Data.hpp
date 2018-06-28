//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_DATA_HPP
#define RAY_TRACING_DATA_HPP

#include <string>
#include "../../Util/File.hpp"
#include "Camera/Camera.hpp"
#include "Light/Light.hpp"
#include "Pigment/Pigment.hpp"
#include "Finishing/Finishing.hpp"
#include "Object/Object.hpp"

namespace RayTracing
{
    class Data
    {

    private:

        Camera*                         camera_;
        std::vector<Light *>            lights_;
        std::vector<Pigment *>          pigments_;
        std::vector<Finishing *>        finishes_;
        std::vector<Object *>           objects_;

    public:

        Data() {}

        void loadFromfile(const std::string& path)
        {
            auto file = std::make_unique<RayTracing::File>(path);
            file->loadFileScene();

            camera_     = file->loadCamera();
            lights_     = file->loadLights();
            pigments_   = file->loadPigments();
            finishes_   = file->loadFinishes();
            objects_    = file->loadObjects();
        }

        void checkIntersection(Ray* ray)
        {
            for (auto object: objects_) {
                object->checkIntersection(ray);
            }
        }

        Camera* getCamera() const
        {
            return camera_;
        }

        std::vector<Pigment*> getPigment() const
        {
            return pigments_;
        }

        std::vector<Object *> getObjects() const
        {
            return objects_;
        }

    };
}

#endif //RAY_TRACING_DATA_HPP
