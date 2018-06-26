//
// Created by luiz0tavio on 6/24/18.
//

#ifndef RAY_TRACING_POLYHEDRON_HPP
#define RAY_TRACING_POLYHEDRON_HPP

#include <glm/vec4.hpp>
#include <vector>
#include "Object.hpp"

namespace RayTracing
{
    class Polyhedron : public Object
    {

    private:

        std::vector<glm::vec4> planes_;

    public:

        Polyhedron(int pigment_index, int finish_index)
                : Object(pigment_index, finish_index), planes_({}) {}

        void addPlane(glm::vec4 plane)
        {
            this->planes_.push_back(plane);
        }
    };
}

#endif //RAY_TRACING_POLYHEDRON_HPP
