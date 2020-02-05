#include <iostream>
#include <vector>
#include <filesystem>

#include "stl.h"

/* 
char[80] (80 bytes) – Header
unsigned long (4 bytes) – Number of triangles

foreach triangle
    float[3] (12 bytes) – Normal vector
    float[3] (12 bytes) – Vertex 1
    float[3] (12 bytes) – Vertex 2
    float[3] (12 bytes) – Vertex 3
    short (2 bytes) – Attribute byte count
end 
*/


int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Usage: mystl model.stl\n";
        return -1;
    }

    auto fname = argv[1];

    std::cout << std::__fs::filesystem::file_size(fname) << std::endl;

    std::ifstream in{fname, std::ifstream::in|std::ifstream::binary};

    unsigned int n_facets = read_number_of_facets(in);

    std::cout << n_facets << std::endl;

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

    std::cout << facets.size() << std::endl;

    in.close();

    return 0;
}