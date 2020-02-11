//
// Created by Oleksandr Semeniuta on 11/02/2020.
//

#include <iostream>
#include "stl.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: scaler model.stl\n";
        return -1;
    }

    auto fname = argv[1];


    std::vector<Facet> facets = read_stl(fname);

    write_stl(facets, "written.stl", "Made by Oleksandr");

}

