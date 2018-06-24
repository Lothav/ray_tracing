//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_FILE_HPP
#define RAY_TRACING_FILE_HPP

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "Util.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Solid.hpp"
#include "Checker.hpp"
#include "TextureMap.hpp"

namespace RayTracing
{
    class File
    {

    public:

        File() = delete;

        static void LoadDataFromFile(const std::string& file_path)
        {
            std::fstream fs;
            fs.open(file_path, std::fstream::in);
            auto file_scene = Util::ReadStream(fs);
            fs.close();

            auto camera_eye     = Util::StdVecToGlmVec3(Util::GetFloats(file_scene[0]));
            auto camera_center  = Util::StdVecToGlmVec3(Util::GetFloats(file_scene[1]));
            auto camera_up      = Util::StdVecToGlmVec3(Util::GetFloats(file_scene[2]));
            auto camera_fov     = Util::GetFloats(file_scene[3])[0];

            auto camera = new RayTracing::Camera(camera_eye, camera_center, camera_up, camera_fov);

            std::vector<RayTracing::Light *> lights;

            auto count_lights = Util::GetFloats(file_scene[4])[0];

            for (int i = 0; i < count_lights; ++i) {

                auto light_data = Util::GetFloats(file_scene[5+i]);

                auto light_pos        = Util::StdVecToGlmVec3({light_data[0], light_data[1], light_data[2]});
                auto light_color      = Util::StdVecToGlmVec3({light_data[3], light_data[4], light_data[5]});
                auto light_mitigation = Util::StdVecToGlmVec3({light_data[6], light_data[7], light_data[8]});

                lights.push_back(new RayTracing::Light(light_pos, light_color, light_mitigation));
            }

            auto pigments_index = 5+count_lights;
            auto total_pigments = Util::GetFloats(file_scene[pigments_index])[0];
            pigments_index++;

            for (int j = 0; j < total_pigments; ++j) {

                auto pigment_tokenize_data = Util::TokenizeString(file_scene[pigments_index+j], ' ');

                auto type = pigment_tokenize_data[0];

                if (type == "solid") {
                    auto solid_data = Util::StdVecToGlmVec3(Util::GetFloats(file_scene[pigments_index+j]));
                    auto pigment = new RayTracing::Solid(solid_data);

                    continue;
                }

                if (type == "checker") {

                    auto checker_data = Util::GetFloats(file_scene[pigments_index+j])

                    auto color_a = Util::StdVecToGlmVec3({checker_data[0], checker_data[1], checker_data[2]});
                    auto color_b = Util::StdVecToGlmVec3({checker_data[3], checker_data[4], checker_data[5]});

                    auto pigment = new RayTracing::Checker(color_a, color_b, checker_data[6]);

                    continue;
                }

                if (type == "texmap") {
                    auto texture_path = pigment_tokenize_data[1];

                    pigments_index++;
                    auto map_vec_1 = Util::StdVecToGlmVec4(Util::GetFloats(file_scene[pigments_index+j]));

                    pigments_index++;
                    auto map_vec_2 = Util::StdVecToGlmVec4(Util::GetFloats(file_scene[pigments_index+j]));

                    auto pigment = new RayTracing::TextureMap(texture_path, map_vec_1, map_vec_2);

                    continue;
                }
            }
        }
    };
}

#endif //RAY_TRACING_FILE_HPP
