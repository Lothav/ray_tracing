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
        std::vector<Pigment *>          pigmentss_;
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
            pigmentss_  = file->loadPigments();
            finishes_   = file->loadFinishes();
            objects_    = file->loadObjects();
        }

    };
}

#endif //RAY_TRACING_DATA_HPP
