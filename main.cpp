//
// Created by luiz0tavio on 6/23/18.
//

#include <iostream>
#include <memory>
#include "RayTracing/File.hpp"

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Must specify at least 2 parameters!" << std::endl;
        return EXIT_FAILURE;
    }

    auto file = std::make_unique<RayTracing::File>(argv[1]);
    file->loadData();

    return EXIT_SUCCESS;
}