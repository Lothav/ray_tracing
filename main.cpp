//
// Created by luiz0tavio on 6/23/18.
//

#include <iostream>
#include <memory>
#include "Util/File.hpp"
#include "RayTracing/Data/Data.hpp"
#include "RayTracing/RayTracing.hpp"

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Must specify at least 2 parameters!" << std::endl;
        return EXIT_FAILURE;
    }

    auto* data = new RayTracing::Data();
    data->loadFromfile(argv[1]);

    auto* ray_tracing = new RayTracing::RayTracing(data);
    ray_tracing->dispatchRay();

    auto file = std::make_unique<RayTracing::File>(argv[2]);
    file->clearFile();
    file->writePPM(200, 100);

    return EXIT_SUCCESS;
}