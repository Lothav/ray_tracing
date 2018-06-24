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
#include "Finishing.hpp"
#include "../Object/Sphere.hpp"
#include "../Object/Polyhedron.hpp"

namespace RayTracing
{
    class File
    {

    private:

        std::vector<std::string> file_scene;

        uint total_lights;
        uint total_pigments;
        uint total_finishes;

        uint jump_index;

    public:

        explicit File(const std::string& file_path) : jump_index(5)
        {
            std::fstream fs;
            fs.open(file_path, std::fstream::in);
            this->file_scene = Util::ReadStream(fs);
            fs.close();
        }

        void loadData()
        {
            this->loadCamera();
            this->loadLights();
            this->loadPigments();
            this->loadFinishes();
            this->loadObjects();
        }

    private:

        void loadCamera()
        {
            auto camera_eye     = Util::StdVecToGlmVec3(Util::GetFloats(file_scene[0]));
            auto camera_center  = Util::StdVecToGlmVec3(Util::GetFloats(file_scene[1]));
            auto camera_up      = Util::StdVecToGlmVec3(Util::GetFloats(file_scene[2]));
            auto camera_fov     = Util::GetFloats(file_scene[3])[0];

            auto camera = new RayTracing::Camera(camera_eye, camera_center, camera_up, camera_fov);

        }

        void loadLights()
        {
            std::vector<RayTracing::Light *> lights = {};

            total_lights = static_cast<uint>(Util::GetFloats(file_scene[4])[0]);

            for (int i = 0; i < total_lights; ++i) {

                auto light_data = Util::GetFloats(file_scene[jump_index+i]);

                auto light_pos        = Util::StdVecToGlmVec3({light_data[0], light_data[1], light_data[2]});
                auto light_color      = Util::StdVecToGlmVec3({light_data[3], light_data[4], light_data[5]});
                auto light_mitigation = Util::StdVecToGlmVec3({light_data[6], light_data[7], light_data[8]});

                lights.push_back(new RayTracing::Light(light_pos, light_color, light_mitigation));
            }

            jump_index += total_lights;
        }

        void loadPigments()
        {
            std::vector<RayTracing::Pigment *> pigments = {};

            total_pigments = static_cast<uint>(Util::GetFloats(file_scene[jump_index])[0]);
            jump_index++;

            for (int j = 0; j < total_pigments; ++j) {

                auto pigment_tokenize_data = Util::TokenizeString(file_scene[jump_index+j], ' ');

                auto type = pigment_tokenize_data[0];

                if (type == "solid") {
                    auto solid_data = Util::StdVecToGlmVec3(Util::GetFloats(file_scene[jump_index+j]));
                    pigments.push_back(new RayTracing::Solid(solid_data));

                    continue;
                }

                if (type == "checker") {

                    auto checker_data = Util::GetFloats(file_scene[jump_index+j]);

                    auto color_a = Util::StdVecToGlmVec3({checker_data[0], checker_data[1], checker_data[2]});
                    auto color_b = Util::StdVecToGlmVec3({checker_data[3], checker_data[4], checker_data[5]});

                    pigments.push_back(new RayTracing::Checker(color_a, color_b, checker_data[6]));

                    continue;
                }

                if (type == "texmap") {
                    auto texture_path = pigment_tokenize_data[1];

                    jump_index++;
                    auto map_vec_1 = Util::StdVecToGlmVec4(Util::GetFloats(file_scene[jump_index+j]));

                    jump_index++;
                    auto map_vec_2 = Util::StdVecToGlmVec4(Util::GetFloats(file_scene[jump_index+j]));

                    pigments.push_back(new RayTracing::TextureMap(texture_path, map_vec_1, map_vec_2));

                    continue;
                }
            }

            jump_index += total_pigments;

        }

        void loadFinishes()
        {
            std::vector<RayTracing::Finishing*> finishes;

            total_finishes = static_cast<uint>(Util::GetFloats(file_scene[jump_index])[0]);
            jump_index++;

            for (int k = 0; k < total_finishes; ++k) {

                auto coefficients = Util::GetFloats(file_scene[jump_index+k]);

                auto light_coefficients = Util::StdVecToGlmVec4({coefficients[0], coefficients[1], coefficients[2], coefficients[3]});
                auto model_coefficients = Util::StdVecToGlmVec3({coefficients[4], coefficients[5], coefficients[6]});

                finishes.push_back(new Finishing(light_coefficients, model_coefficients));
            }

            jump_index += total_finishes;
        }

        void loadObjects()
        {
            std::vector<Object::Object *> objects = {};

            auto total_objects = Util::GetFloats(file_scene[jump_index])[0];
            jump_index++;

            for (int l = 0; l < total_objects; ++l) {

                auto objects_data_indexes  = Util::GetFloats(file_scene[jump_index+l]);
                auto pigment_tokenize_data = Util::TokenizeString(file_scene[jump_index+l], ' ');

                auto type           = pigment_tokenize_data[2];
                auto pigment_index  = objects_data_indexes[0];
                auto finish_index   = objects_data_indexes[1];

                if (type == "sphere") {

                    objects.push_back(
                        new Object::Sphere(
                            static_cast<int>(pigment_index),
                            static_cast<int>(finish_index),
                            {objects_data_indexes[2], objects_data_indexes[3], objects_data_indexes[4]},
                            objects_data_indexes[5]
                        )
                    );

                    continue;
                }

                if (type == "polyhedron") {

                    auto polyhedron = new Object::Polyhedron(static_cast<int>(pigment_index), static_cast<int>(finish_index));

                    for (int i = 0; i < objects_data_indexes[2]; ++i) {
                        jump_index++;
                        auto plane = Util::StdVecToGlmVec4(Util::GetFloats(file_scene[jump_index+l]));
                        polyhedron->addPlane(plane);
                    }

                    objects.push_back(polyhedron);
                    continue;
                }
            }
        }

    };
}

#endif //RAY_TRACING_FILE_HPP
