//
// Created by luiz0tavio on 6/23/18.
//

#include <iostream>
#include <memory>
#include "Util/File.hpp"
#include "RayTracing/Data/Data.hpp"

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Must specify at least 2 parameters!" << std::endl;
        return EXIT_FAILURE;
    }

    auto ray_tracing_data = new RayTracing::Data();
    ray_tracing_data->loadFromfile(argv[1]);

    auto file = std::make_unique<RayTracing::File>(argv[2]);
    file->clearFile();
    file->writeOnFile();

    return EXIT_SUCCESS;
}