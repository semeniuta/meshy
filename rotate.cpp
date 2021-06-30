#include <iostream>
#include "stl.h"
#include "geometry.h"

int main(int argc, char *argv[]) {

    if (argc < 5) {
        std::cout << "Usage: rotate model.stl rotz roty rotx\n";
        return -1;
    }

    char *fname = argv[1];
    double rotz = std::stod(argv[2]);
    double roty = std::stod(argv[3]);
    double rotx = std::stod(argv[4]);

    std::vector<Facet> facets = read_stl(fname);

    auto Rx = rotation_matrix_x(rotx);
    auto Ry = rotation_matrix_y(roty);
    auto Rz = rotation_matrix_z(rotz);

    auto R = Rz * Ry * Rx;

    MatrixXd R_h = MatrixXd::Identity(4, 4);
    R_h.block<3, 3>(0, 0) = R;

    auto transformed_facets = transform_facets(facets, R_h);
    write_stl(transformed_facets, "rotated.stl", "Rotated using meshy");

}