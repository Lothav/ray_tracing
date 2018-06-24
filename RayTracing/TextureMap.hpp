//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_TEXTUREMAP_HPP
#define RAY_TRACING_TEXTUREMAP_HPP

#include "Pigments.hpp"
#include <string>
#include <glm/vec4.hpp>
#include <utility>

namespace RayTracing
{
    class TextureMap : protected Pigments
    {

    private:

        std::string texture_path_;

        glm::vec4   map_vec_1_;
        glm::vec4   map_vec_2_;

    public:

        TextureMap(std::string texture_path, glm::vec4 map_vec_1, glm::vec4 map_vec_2)
                : texture_path_(std::move(texture_path)), map_vec_1_(map_vec_1), map_vec_2_(map_vec_2) {}
    };
}

#endif //RAY_TRACING_TEXTUREMAP_HPP
