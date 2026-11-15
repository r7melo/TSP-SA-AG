#pragma once

#include "tsp.h"

typedef struct {
    int *nodes_index;
    int dimension;
    int total_dist;
} PATH;

void DeconstructPath(PATH *path);
PATH *ConstructPath(TSP *tsp);
int DistanceBetweenNodes(Node a, Node b);
void CalculatePathCost(TSP *tsp, PATH *path);
int* GenerateRandomPath(int dimension);