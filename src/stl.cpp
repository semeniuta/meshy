#include "stl.h"

unsigned int read_number_of_facets(std::ifstream& in) {

    STLMetadata meta{};

    in.read(meta.header,   sizeof(meta.header));
    in.read(meta.n_facets, sizeof(meta.n_facets));

    unsigned int n_facets;
    std::memcpy(&n_facets, meta.n_facets, 4);

    return n_facets;
}

void parse_point(char* buf, float* arr) {
    for (int i = 0; i < 3; i++) {
        float* dst_addr = arr + i;
        std::memcpy(dst_addr, buf + 4*i, 4);
    }
}