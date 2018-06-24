//
// Created by luiz0tavio on 6/23/18.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "RayTracing/Camera.hpp"
#include "RayTracing/Light.hpp"
#include "RayTracing/Solid.hpp"
#include "RayTracing/Checker.hpp"
#include "RayTracing/TextureMap.hpp"

std::vector<std::string> readStream(std::istream& input_stream)
{
    std::vector<std::string> lines;

    std::string line;
    while (!input_stream.eof()) {
        if (std::getline(input_stream, line)) {
            lines.push_back(line);
        }
    }

    return lines;
}

std::vector<float> getFloats(std::string data_string)
{
    std::vector<float> data_f = {};

    std::regex r("[+-]?([0-9]*[.])?[0-9]+");
    std::smatch m;

    while (std::regex_search(data_string, m, r)) {
        auto val_f = std::stof(m[0]);
        data_f.push_back(val_f);
        data_string = m.suffix().str();
    }

    return data_f;
}

glm::vec3 stdVecToGlmVec3(const std::vector<float>& std_vec)
{
    if (std_vec.size() != 3) throw std::bad_function_call();

    glm::vec3 glm_vec;
    for (int i = 0; i < std_vec.size(); ++i) {
        glm_vec[i] = std_vec[i];
    }

    return glm_vec;
}

glm::vec4 stdVecToGlmVec4(const std::vector<float>& std_vec)
{
    if (std_vec.size() != 4) throw std::bad_function_call();

    glm::vec4 glm_vec;
    for (int i = 0; i < std_vec.size(); ++i) {
        glm_vec[i] = std_vec[i];
    }

    return glm_vec;
}

std::vector<std::string> tokenizeString(const std::string& string, char separator)
{
    std::vector<std::string> ret = {};

    std::istringstream iss(string);
    std::string token;
    while (std::getline(iss, token, separator)) {
        ret.push_back(token);
    }

    return ret;
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Must specify at least 2 parameters!" << std::endl;
        return EXIT_FAILURE;
    }

    std::fstream fs;
    fs.open(argv[1], std::fstream::in);
    auto file_scene = readStream(fs);
    fs.close();

    auto camera_eye     = stdVecToGlmVec3(getFloats(file_scene[0]));
    auto camera_center  = stdVecToGlmVec3(getFloats(file_scene[1]));
    auto camera_up      = stdVecToGlmVec3(getFloats(file_scene[2]));
    auto camera_fov     = getFloats(file_scene[3])[0];

    auto camera = new RayTracing::Camera(camera_eye, camera_center, camera_up, camera_fov);

    std::vector<RayTracing::Light *> lights;

    auto count_lights = getFloats(file_scene[4])[0];

    for (int i = 0; i < count_lights; ++i) {

        auto light_data = getFloats(file_scene[5+i]);

        auto light_pos        = stdVecToGlmVec3({light_data[0], light_data[1], light_data[2]});
        auto light_color      = stdVecToGlmVec3({light_data[3], light_data[4], light_data[5]});
        auto light_mitigation = stdVecToGlmVec3({light_data[6], light_data[7], light_data[8]});

        lights.push_back(new RayTracing::Light(light_pos, light_color, light_mitigation));
    }

    auto pigments_index = 5+count_lights;
    auto total_pigments = getFloats(file_scene[pigments_index])[0];
    pigments_index++;

    for (int j = 0; j < total_pigments; ++j) {

        auto pigment_tokenize_data = tokenizeString(file_scene[pigments_index+j], ' ');

        auto type = pigment_tokenize_data[0];

        if (type == "solid") {
            auto solid_data = stdVecToGlmVec3(getFloats(file_scene[pigments_index+j]));
            auto pigment = new RayTracing::Solid(solid_data);

            continue;
        }

        if (type == "checker") {

            auto checker_data = getFloats(file_scene[pigments_index+j]);

            auto color_a = stdVecToGlmVec3({checker_data[0], checker_data[1], checker_data[2]});
            auto color_b = stdVecToGlmVec3({checker_data[3], checker_data[4], checker_data[5]});

            auto pigment = new RayTracing::Checker(color_a, color_b, checker_data[6]);

            continue;
        }

        if (type == "texmap") {
            auto texture_path = pigment_tokenize_data[1];

            pigments_index++;
            auto map_vec_1 = stdVecToGlmVec4(getFloats(file_scene[pigments_index+j]));

            pigments_index++;
            auto map_vec_2 = stdVecToGlmVec4(getFloats(file_scene[pigments_index+j]));

            auto pigment = new RayTracing::TextureMap(texture_path, map_vec_1, map_vec_2);

            continue;
        }
    }

    return EXIT_SUCCESS;
}