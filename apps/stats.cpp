#include <iostream>
#include "stl.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: stats model.stl\n";
        return -1;
    }

    auto fname = argv[1];
    std::vector<Facet> facets = read_stl(fname);

    std::cout << "Number of facets: " << facets.size() << "\n";

    return 0;
}