//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_UTIL_HPP
#define RAY_TRACING_UTIL_HPP

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <string>
#include <regex>


namespace RayTracing
{
    class Util
    {

    public:

        Util() = delete;

        static std::vector<std::string> ReadStream(std::istream& input_stream)
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

        static std::vector<float> GetFloats(std::string data_string)
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

        static glm::vec3 StdVecToGlmVec3(const std::vector<float>& std_vec)
        {
            if (std_vec.size() != 3) throw std::bad_function_call();

            glm::vec3 glm_vec;
            for (int i = 0; i < std_vec.size(); ++i) {
                glm_vec[i] = std_vec[i];
            }

            return glm_vec;
        }

        static glm::vec4 StdVecToGlmVec4(const std::vector<float>& std_vec)
        {
            if (std_vec.size() != 4) throw std::bad_function_call();

            glm::vec4 glm_vec;
            for (int i = 0; i < std_vec.size(); ++i) {
                glm_vec[i] = std_vec[i];
            }

            return glm_vec;
        }

        static std::vector<std::string> TokenizeString(const std::string& string, char separator)
        {
            std::vector<std::string> ret = {};

            std::istringstream iss(string);
            std::string token;
            while (std::getline(iss, token, separator)) {
                ret.push_back(token);
            }

            return ret;
        }

    };
}


#endif //RAY_TRACING_UTIL_HPP
