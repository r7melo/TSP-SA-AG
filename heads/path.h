#pragma once

#include "tsp.h"

typedef struct {
    int *nodes_index;
    int dimension;
} PATH;

void DeconstructPath(PATH *path);
PATH *ConstructPath(TSP *tsp);
int DistanceBetweenNodes(Node a, Node b);
int CalculatePathTotalDist(TSP *tsp, PATH *path);
int* GenerateRandomPath(int dimension);