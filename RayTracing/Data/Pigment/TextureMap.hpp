//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_TEXTUREMAP_HPP
#define RAY_TRACING_TEXTUREMAP_HPP

#include "Pigment.hpp"
#include "../../../Util/Util.hpp"
#include <string>
#include <glm/vec4.hpp>
#include <utility>
#include <fstream>
#include <iostream>
#include <glm/geometric.hpp>

namespace RayTracing
{
    class TextureMap : public Pigment
    {

    private:

        std::string                 texture_path_;

        glm::vec4                   map_vec_1_;
        glm::vec4                   map_vec_2_;

        std::vector<std::string>    data_;

    public:

        TextureMap(std::string texture_path, glm::vec4 map_vec_1, glm::vec4 map_vec_2)
                : texture_path_(std::move(texture_path)), map_vec_1_(map_vec_1), map_vec_2_(map_vec_2)
        {
            std::fstream fs;
            fs.open(texture_path_, std::fstream::in);

            if (!fs.is_open()) {
                std::cerr << "Cant open file "  << texture_path_ << std::endl;
            }

            this->data_ = Util::ReadStream(fs);
            fs.close();
        }

        glm::vec3 getColor(glm::vec3 intersection, double u, double v) override
        {
            int nx = 467;
            int ny = 350;

            double i = (u * nx);
            double j = (1 - v)*ny - 0.001;

            if(i < 0) i = 0;
            if(j < 0) j = 0;
            if(i > nx - 1) i = nx - 1;
            if(j > ny - 1) j = ny - 1;

            auto base_index = static_cast<int>(3*i + 3*nx*j + 2 + 4);
            if (base_index % 3 != 0) {
                if ((base_index+1) % 3  == 0){
                    base_index += 1;
                } else if ((base_index-1) % 3  == 0) {
                    base_index -= 1;
                } else {
                    std::cerr << "Error base index texture mapping: " << base_index << std::endl;
                }
            }

            float r = std::stoi(data_[base_index - 2]) / 255.0f;
            float g = std::stoi(data_[base_index - 1]) / 255.0f;
            float b = std::stoi(data_[base_index - 0]) / 255.0f;

            return glm::vec3(r, g, b);
        }
    };
}

#endif //RAY_TRACING_TEXTUREMAP_HPP
