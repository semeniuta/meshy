//
// Created by Oleksandr Semeniuta on 09/04/2020.
//

#ifndef MESHY_GEOMETRY_H
#define MESHY_GEOMETRY_H

#include "stl.h"

double euclidean_distance(const VectorXd& v1, const VectorXd& v2);

double triangle_area(const Facet& facet);

#endif //MESHY_GEOMETRY_H
