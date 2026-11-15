#pragma once

#include "tsp.h"
#include "graph.h"

typedef struct {
    int *nodes;
    int count;
    int capacity;
    double total_dist;
} PATH;

PATH *BuildTour(TSP *tsp, GRAPH *graph);
void DeconstructPath(PATH *path);