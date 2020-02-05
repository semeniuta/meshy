#include <fstream>

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
    float normal[3];
    float v1[3];
    float v2[3];
    float v3[3];
};

unsigned int read_number_of_facets(std::ifstream& in);

void parse_point(char* buf, float* arr);