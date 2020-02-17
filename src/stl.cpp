#include "stl.h"
#include <iostream>

unsigned int read_number_of_facets(std::ifstream& in) {

    STLMetadata meta{};

    in.read(meta.header, sizeof(meta.header));
    in.read(meta.n_facets, sizeof(meta.n_facets));

    char h[81];
    std::memcpy(h, meta.header, 80);
    h[80] = '\0';
    std::cout << "Header: " << h << std::endl;

    unsigned int n_facets;
    std::memcpy(&n_facets, meta.n_facets, 4);

    std::cout << "Number of facets: " << n_facets << std::endl;

    return n_facets;
}

VectorXd parse_point(char* buf) {

    float arr[3];
    VectorXd vec{3};

    for (int i = 0; i < 3; i++) {
        float* dst_addr = arr + i;
        std::memcpy(dst_addr, buf + 4 * i, 4);
        vec(i) = arr[i];
    }

    return vec;
}

std::vector<Facet> read_stl(const std::string& fname) {

    std::ifstream in{fname, std::ifstream::in|std::ifstream::binary};

    unsigned int n_facets = read_number_of_facets(in);

    FacetBuffer fbuf{};
    std::vector<Facet> facets;

    while(in.good()) {

        in.read(fbuf.normal,     sizeof(fbuf.normal));
        in.read(fbuf.v1,         sizeof(fbuf.v1));
        in.read(fbuf.v2,         sizeof(fbuf.v2));
        in.read(fbuf.v3,         sizeof(fbuf.v3));
        in.read(fbuf.byte_count, sizeof(fbuf.byte_count));

        if (!in.eof()) {

            Facet facet{};
            facet.normal = parse_point(fbuf.normal);
            facet.v1 = parse_point(fbuf.v1);
            facet.v2 = parse_point(fbuf.v2);
            facet.v3 = parse_point(fbuf.v3);

            facets.push_back(facet);
        }

    }

    in.close();

    if (n_facets != facets.size()) {
        throw std::runtime_error("Number of facets mismatch");
    }

    return facets;

}

void fill_point_data(const VectorXd& v, char* dst) {

    for (int i = 0; i < 3; i++) {
        auto x = (float)v(i);
        std::memcpy(dst + 4 * i, &x, 4);
    }
}

void write_stl(const std::vector<Facet>& facets, const std::string& fname, const std::string& header) {

    std::ofstream out{fname};

    char h[80];
    std::fill(h, h+80, 0);
    std::memcpy(h, header.c_str(), 80);
    std::cout << "New header: " << h << std::endl;

    auto nf = facets.size();
    char n_facets[4];
    std::memcpy(n_facets, &nf, 4);

    out.write(h, 80);
    out.write(n_facets, 4);

    char point_buf[12];
    char byte_count[2] = {0, 0};

    for (const auto& facet : facets) {

        fill_point_data(facet.normal, point_buf);
        out.write(point_buf, 12);

        fill_point_data(facet.v1, point_buf);
        out.write(point_buf, 12);

        fill_point_data(facet.v2, point_buf);
        out.write(point_buf, 12);

        fill_point_data(facet.v3, point_buf);
        out.write(point_buf, 12);

        out.write(byte_count, 2);
    }

    out.close();

}

VectorXd transform_point(const VectorXd& p, const MatrixXd& T) {

    auto space_size = p.size();
    auto homog_size = space_size + 1;

    if ((T.rows() != T.cols()) || (homog_size != T.cols())) {
        throw std::runtime_error("Dimension mismatch");
    }

    VectorXd p_h{homog_size};
    p_h.head(space_size) = p;
    p_h(homog_size - 1) = 1.;

    auto p_t = T * p_h;

    VectorXd result{space_size};
    result = p_t.head(space_size) / p_t(space_size);

    return result;

}

VectorXd normal_vector(const Vector3d& a, const Vector3d& b, const Vector3d& c) {

    auto ab = b - a;
    auto ac = c - a;

    auto n = ab.cross(ac);

    return n.normalized();

}

std::vector<Facet> transform_facets(const std::vector<Facet>& facets, const MatrixXd& T) {

    std::vector<Facet> transformed_facets;

    for (const auto& f : facets) {

        auto v1t = transform_point(f.v1, T);
        auto v2t = transform_point(f.v2, T);
        auto v3t = transform_point(f.v3, T);

        auto n_t = normal_vector(v1t, v2t, v3t);

        Facet f_t{
            n_t,
            v1t,
            v2t,
            v3t
        };

        transformed_facets.push_back(f_t);

    }

    return transformed_facets;

}