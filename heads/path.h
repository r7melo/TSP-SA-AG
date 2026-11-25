#pragma once

#include "tsp.h"

typedef struct {
    char name[64];
    int *nodes_index;
    int dimension;
    int total_weight;
} PATH;

PATH *ConstructPath(TSP *tsp);
void DeconstructPath(PATH *path);
int DistanceBetweenNodes(Node a, Node b);
int CalculatePathTotalDist(TSP *tsp, PATH *path);
int* GenerateRandomPath(int dimension);
PATH *PathCopy(const PATH *path);
PATH *PathCopyVoid(const PATH *path);
PATH *PathCopyPartial(const PATH *path, size_t c1, size_t c2);