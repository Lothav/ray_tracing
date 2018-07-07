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

        glm::vec3 getColor(glm::vec3 intersection) override
        {
            //auto s = glm::dot(map_vec_1_, glm::vec4(intersection, 1.f));
            //auto t = glm::dot(map_vec_2_, glm::vec4(intersection, 1.f));

            //auto index = (467/2) + static_cast<int>(s * 467);

            auto r = 0.f; //std::stoi(data_[index])/255.99f;
            auto g = 0.f; //std::stoi(data_[index+1])/255.99f;
            auto b = 0.f; //std::stoi(data_[index+2])/255.99f;

            return glm::vec3(r, g, b);
        }
    };
}

#endif //RAY_TRACING_TEXTUREMAP_HPP
