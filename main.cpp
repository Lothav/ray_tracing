//
// Created by luiz0tavio on 6/23/18.
//

#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> readStream(std::istream& input_stream)
{
    std::vector<std::string> lines;

    std::string line;
    while (!input_stream.eof()) {
        if (std::getline(input_stream, line)) {
            lines.push_back(line);
        }
    }

    return lines;
}


int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Must specify at least 2 parameters!" << std::endl;
        return EXIT_FAILURE;
    }

    std::fstream fs;
    fs.open(argv[1], std::fstream::in);
    auto stream = readStream(fs);
    fs.close();

    return EXIT_SUCCESS;
}