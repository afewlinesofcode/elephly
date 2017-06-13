#include <iostream>
#include <fstream>
#include <stdexcept>
#include <boost/locale.hpp>
#include "Elephly/Elephly.h"

int main(int argc, char* argv[])
{
    using namespace std;

    ios_base::sync_with_stdio(false);

    boost::locale::generator gen;
    locale::global(std::locale { gen("") });

    // Require 1 + 2 parameters
    if (argc < 3)
        throw std::runtime_error("Insufficient parameters");

    // Setting up stream with words and dict
    std::wifstream words { argv[1] };
    std::wifstream dict { argv[2] };

    if (!words.good())
        throw std::runtime_error("Unable to read words");

    if (!dict.good())
        throw std::runtime_error("Unable to read dictionary");

    // Effective path finder
    Elephly::Elephly elephly;

    words >> elephly.words();
    dict >> elephly.dict();

    auto path = elephly.run();

    if (path.size() == 1)
        std::wcout << "Destination unreachable" << std::endl;
    else
        std::wcout << "PATH:" << std::endl << path << std::endl;

    return 0;
}

