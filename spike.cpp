//
// Created by Oleksandr Semeniuta on 05/02/2020.
//

#include <iostream>
#include <vector>
#include "stl.h"

using Eigen::VectorXd;

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "Usage: spike model.stl\n";
        return -1;
    }

    auto fname = argv[1];
    std::vector<Facet> facets = read_stl(fname);

    std::cout << facets.size() << std::endl;

    std::cout << facets[0].normal << std::endl;

    return 0;
}