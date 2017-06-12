#include <iostream>
#include <fstream>
#include <stdexcept>
#include <boost/locale.hpp>

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);

    boost::locale::generator gen;
    std::locale::global(std::locale { gen("") });

    return 0;
}

