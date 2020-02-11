#ifndef MESHY_STL_H
#define MESHY_STL_H

#include <fstream>
#include <vector>
#include <Eigen/Dense>

using Eigen::VectorXd;
using Eigen::MatrixXd;

struct STLMetadata {
    char header[80];
    char n_facets[4];
};

struct FacetBuffer {
    char normal[12];
    char v1[12];
    char v2[12];
    char v3[12];
    char byte_count[2];
};

struct Facet {
    VectorXd normal;
    VectorXd v1;
    VectorXd v2;
    VectorXd v3;
};

unsigned int read_number_of_facets(std::ifstream &in);

VectorXd parse_point(char* buf);

void fill_point_data(const VectorXd& v, char* dst);

std::vector<Facet> read_stl(const std::string& fname);

void write_stl(const std::vector<Facet>& facets, const std::string& fname, const std::string& header);

VectorXd transform_point(const VectorXd& p, const MatrixXd& T);

std::vector<Facet> transform_facets(const std::vector<Facet>& facets, const MatrixXd& T);

#endif //MESHY_STL_H
