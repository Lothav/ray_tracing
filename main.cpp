//
// Created by luiz0tavio on 6/23/18.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "Camera.hpp"

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

std::vector<float> getIntsFromString(std::string data_string)
{
    std::vector<float> data_int = {};

    std::regex r("(\\+|-)?[[:digit:]]+");
    std::smatch m;

    while (std::regex_search(data_string, m, r)) {
        data_int.push_back( std::stoi (m[0]) );
        data_string = m.suffix().str();
    }

    return data_int;
}

glm::vec3 stdVectorToGlmVector(const std::vector<float>& std_vec)
{
    if (std_vec.size() != 3) throw std::bad_function_call();

    glm::vec3 glm_vec;
    for (int i = 0; i < std_vec.size(); ++i) {
        glm_vec[i] = std_vec[i];
    }

    return glm_vec;
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

    auto camera_eye     = stdVectorToGlmVector(getIntsFromString(file_scene[0]));
    auto camera_center  = stdVectorToGlmVector(getIntsFromString(file_scene[1]));
    auto camera_up      = stdVectorToGlmVector(getIntsFromString(file_scene[2]));

    auto camera = new Camera(camera_eye, camera_center, camera_up);

    return EXIT_SUCCESS;
}