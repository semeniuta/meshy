/**
 * Read an STL file, scale the mesh with a
 * homogeneous transformation, and save the
 * scaled mesh.
 */

#include <iostream>
#include "stl.h"


int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: scaler model.stl\n";
        return -1;
    }

    auto fname = argv[1];

    std::vector<Facet> facets = read_stl(fname);

    double scale_x = 1.;
    double scale_y = 1.;
    double scale_z = 2.;

    MatrixXd T = MatrixXd::Identity(4, 4);
    T(0, 0) = scale_x;
    T(1, 1) = scale_y;
    T(2, 2) = scale_z;

    auto transformed_facets = transform_facets(facets, T);

    write_stl(transformed_facets, "written.stl", "Made by Oleksandr");

}

