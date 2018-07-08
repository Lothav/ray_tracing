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

        std::string                             texture_path_;

        glm::vec4                               map_vec_1_;
        glm::vec4                               map_vec_2_;

        std::vector<std::vector<glm::vec3>>     data_;
        uint                                    nx;
        uint                                    ny;
        uint                                    range;

    public:

        TextureMap(std::string texture_path, glm::vec4 map_vec_1, glm::vec4 map_vec_2)
                : texture_path_(std::move(texture_path)), map_vec_1_(map_vec_1), map_vec_2_(map_vec_2)
        {
            std::fstream fs;
            fs.open(texture_path_, std::fstream::in);

            if (!fs.is_open()) {
                std::cerr << "Cant open file "  << texture_path_ << std::endl;
            }

            auto file_data = Util::ReadStream(fs);

            int i = 0;
            for (; i < file_data.size(); i++) {

                if (file_data[i][0] == '#') continue;
                if (file_data[i][0] == 'P') continue;

                auto size = Util::GetFloats(file_data[i]);
                if (size.size() != 2) std::cerr << "Error format ppm file" << std::endl;
                nx = static_cast<uint>(size[0]);
                ny = static_cast<uint>(size[1]);

                i++;
                auto range_f = Util::GetFloats(file_data[i]);
                if (range_f.size() != 1) std::cerr << "Error format ppm file" << std::endl;
                range = static_cast<uint>(range_f[0]);
                i++;

                break;
            }

            for (uint j = 0; j < nx; ++j) {
                data_.resize(j+1);
                for (uint k = 0; k < ny; ++k) {
                    auto base_index = static_cast<int>(3*j + 3*nx*k + 2 + i);
                    if (base_index % 3 != 0) {
                        if ((base_index+1) % 3  == 0){
                            base_index += 1;
                        } else if ((base_index-1) % 3  == 0) {
                            base_index -= 1;
                        } else {
                            std::cerr << "Error base index texture mapping: " << base_index << std::endl;
                        }
                    }

                    auto grb = glm::vec3(
                        std::stoi(file_data[base_index - 2]) / 255.f,
                        std::stoi(file_data[base_index - 1]) / 255.f,
                        std::stoi(file_data[base_index - 0]) / 255.f
                    );

                    data_[j].resize(k+1);
                    data_[j][k] = grb;
                }
            }

            fs.close();
        }

        glm::vec3 getColor(glm::vec3 intersection, double u, double v) override
        {
            double i = (u * nx);
            double j = (1 - v)*ny - 0.001;

            if(i < 0) i = 0;
            if(j < 0) j = 0;
            if(i > nx - 1) i = nx - 1;
            if(j > ny - 1) j = ny - 1;

            return data_[i][j];
        }
    };
}

#endif //RAY_TRACING_TEXTUREMAP_HPP
