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

    auto data = std::make_shared<RayTracing::Data>();
    data->loadFromfile(argv[1]);

    auto ray_tracing = std::make_unique<RayTracing::RayTracing>(data.get());
    ray_tracing->fillColorMap();

    auto file = std::make_unique<RayTracing::File>(argv[2]);
    file->clearFile();
    file->writePPM(ray_tracing->getColorMap());

    return EXIT_SUCCESS;
}