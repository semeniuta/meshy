#include "stl.h"

unsigned int read_number_of_facets(std::ifstream& in) {

    STLMetadata meta{};

    in.read(meta.header, sizeof(meta.header));
    in.read(meta.n_facets, sizeof(meta.n_facets));

    unsigned int n_facets;
    std::memcpy(&n_facets, meta.n_facets, 4);

    return n_facets;
}

void parse_point(char* buf, float* arr) {
    for (int i = 0; i < 3; i++) {
        float* dst_addr = arr + i;
        std::memcpy(dst_addr, buf + 4 * i, 4);
    }
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
            parse_point(fbuf.normal, facet.normal);
            parse_point(fbuf.v1,     facet.v1);
            parse_point(fbuf.v2,     facet.v2);
            parse_point(fbuf.v3,     facet.v3);

            facets.push_back(facet);
        }

    }

    in.close();

    if (n_facets != facets.size()) {
        throw std::runtime_error("Number of facets mismatch");
    }

    return facets;

}