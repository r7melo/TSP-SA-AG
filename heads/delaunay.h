#pragma once

#include <stdbool.h>
#include "triangles.h"
#include "polygon.h"


static bool triangle_has_super_vertex(TRIANGLE triangle, int n);
static bool point_in_circumcircle(TSP *tsp, TRIANGLE triangle, int p);
TRIANGLES *BuildDelaunay(TSP *tsp);