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
    };
}

#endif //RAY_TRACING_TEXTUREMAP_HPP
